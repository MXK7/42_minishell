/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_handler.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arazzok <arazzok@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 18:31:43 by arazzok           #+#    #+#             */
/*   Updated: 2024/01/23 12:48:07 by arazzok          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	push_lexer(t_lexer **list, t_lexer *new)
{
	t_lexer	*temp;

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

int	add_redirection(t_lexer *temp, t_parser *parser)
{
	t_lexer	*node;
	int		first_index;
	int		second_index;

	node = init_lexer(temp->next->str, temp->token);
	if (!node)
		parser_error(2, parser->global, parser->lexer_list);
	push_lexer(&parser->redirections, node);
	first_index = temp->index;
	second_index = temp->next->index;
	del_one(&parser->lexer_list, first_index);
	del_one(&parser->lexer_list, second_index);
	parser->nb_redirections++;
	return (0);
}

void	del_redirections(t_parser *parser)
{
	t_lexer	*temp;

	temp = parser->lexer_list;
	while (temp && temp->token == WORD)
		temp = temp->next;
	if (!temp || temp->token == PIPE)
		return ;
	if (!temp->next)
		parser_error(0, parser->global, parser->lexer_list);
	if (temp->next->token && temp->next->token != WORD)
		double_token_error(parser->global, parser->lexer_list,
			temp->next->token);
	if (temp->token >= RIGHT && temp->token <= DOUBLE_LEFT)
		add_redirection(temp, parser);
	del_redirections(parser);
}
