/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arazzok <arazzok@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/22 14:25:43 by arazzok           #+#    #+#             */
/*   Updated: 2024/01/07 23:29:11 by arazzok          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_lexer	*init_lexer(char *str, t_token token)
{
	t_lexer		*node;
	static int	i = 0;

	node = malloc(sizeof(t_lexer));
	if (!node)
		return (NULL);
	node->str = ft_strdup(str);
	node->token = token;
	node->index = i++;
	node->prev = NULL;
	node->next = NULL;
	return (node);
}

void	clear_one(t_lexer **list)
{
	if ((*list)->str)
	{
		free((*list)->str);
		(*list)->str = NULL;
	}
	free(*list);
	*list = NULL;
}

void	del_first(t_lexer **list)
{
	t_lexer	*temp;

	temp = *list;
	*list = temp->next;
	clear_one(&temp);
	if (*list)
		(*list)->prev = NULL;
}

void	del_one(t_lexer **list, int index)
{
	t_lexer	*temp;
	t_lexer	*prev;
	t_lexer	*start;

	start = *list;
	temp = start;
	if ((*list)->index == index)
	{
		del_first(list);
		return ;
	}
	while (temp && temp->index != index)
	{
		prev = temp;
		temp = temp->next;
	}
	if (temp)
		prev->next = temp->next;
	else
		prev->next = NULL;
	if (prev->next)
		prev->next->prev = prev;
	clear_one(&temp);
	*list = start;
}

void	free_lexer(t_lexer **list)
{
	t_lexer	*temp;

	if (!*list)
		return ;
	while (*list)
	{
		temp = (*list)->next;
		if ((*list)->str)
			free((*list)->str);
		free(*list);
		*list = temp;
	}
	*list = NULL;
}
