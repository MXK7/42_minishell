/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arazzok <arazzok@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 11:31:55 by arazzok           #+#    #+#             */
/*   Updated: 2024/01/11 18:24:39 by arazzok          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_parser	init_parser(t_global *global)
{
	t_parser	node;

	node.lexer_list = global->lexer_list;
	node.redirections = NULL;
	node.nb_redirections = 0;
	node.global = global;
	return (node);
}

void	count_pipes(t_global *global)
{
	t_lexer	*temp;

	temp = global->lexer_list;
	while (temp)
	{
		if (temp->token == PIPE)
			global->nb_pipes++;
		temp = temp->next;
	}
}

int	count_args(t_lexer *lexer_list)
{
	int		nb_args;
	t_lexer	*temp;

	;
	nb_args = 0;
	temp = lexer_list;
	while (temp && temp->token != PIPE)
	{
		if (temp->index >= 0)
			nb_args++;
		temp = temp->next;
	}
	return (nb_args);
}
