/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_command_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arazzok <arazzok@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 23:42:16 by arazzok           #+#    #+#             */
/*   Updated: 2024/01/11 18:13:51 by arazzok          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_command	*init_command(char **str, int nb_redirections, t_lexer *redirections)
{
	t_command	*node;

	node = malloc(sizeof(t_command));
	if (!node)
		return (NULL);
	node->str = str;
	// node->builtin = builtin_arr(str[0]);
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
