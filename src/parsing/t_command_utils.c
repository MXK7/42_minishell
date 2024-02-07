/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_command_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arazzok <arazzok@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 23:42:16 by arazzok           #+#    #+#             */
/*   Updated: 2024/02/07 15:36:52 by arazzok          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_command	*init_command(char **str, int nb_redirections,
		t_lexer *redirections)
{
	t_command	*node;

	node = malloc(sizeof(t_command));
	if (!node)
		return (NULL);
	node->str = str;
	node->heredoc_file_name = NULL;
	node->nb_redirections = nb_redirections;
	node->redirections = redirections;
	node->prev = NULL;
	node->next = NULL;
	return (node);
}

void	push_command(t_command **list, t_command *new)
{
	t_command	*temp;

	temp = *list;
	if (*list == NULL)
	{
		*list = new;
		return ;
	}
	while (temp->next)
		temp = temp->next;
	temp->next = new;
	new->prev = temp;
}

void	free_command(t_command **list)
{
	t_command	*temp;
	t_lexer		*redirections_temp;

	if (*list == NULL)
		return ;
	while (*list)
	{
		temp = (*list)->next;
		redirections_temp = (*list)->redirections;
		free_lexer(&redirections_temp);
		if ((*list)->str)
			free_array((*list)->str);
		if ((*list)->heredoc_file_name)
			free((*list)->heredoc_file_name);
		free(*list);
		*list = temp;
	}
	*list = NULL;
}

t_command	*command_first(t_command *list)
{
	if (!list)
		return (NULL);
	while (list->prev)
		list = list->prev;
	return (list);
}
