/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_command_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arazzok <arazzok@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 23:42:16 by arazzok           #+#    #+#             */
/*   Updated: 2024/01/07 23:43:41 by arazzok          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_command	*init_command(void)
{
	t_command	*node;

	node = malloc(sizeof(t_command));
	if (!node)
		return (NULL);
	node->str = (char **) malloc(sizeof(char *));
	if (!node->str)
		return (free(node), NULL);
	node->str[0] = NULL;
    node->builtin = NULL;
    node->heredoc_file_name = NULL;
    node->nb_redirections = 0;
    node->redirections = NULL;
    node->next = NULL;
    node->prev = NULL;
	return (node);
}
