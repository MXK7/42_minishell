/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arazzok <arazzok@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 21:50:36 by mpoussie          #+#    #+#             */
/*   Updated: 2023/12/29 19:53:53 by arazzok          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_command	*init_command(void)
{
	t_command	*node;

	node = malloc(sizeof(t_command));
	if (!node)
		return (NULL);
	node->str = NULL;
	node->builtin = NULL;
	node->nb_redirections = 0;
	node->heredoc_file_name = NULL;
	node->redirections = NULL;
	node->prev = NULL;
	node->next = NULL;
	return (node);
}

t_command	*tokens_to_commands(t_lexer *lexer)
{
	t_command	*head;
	t_command	*current;

	head = NULL;
	current = NULL;
	while (lexer)
	{
		current = init_command();
		while (lexer && lexer->token != PIPE)
		{
			handle_token(lexer, current);
			lexer = lexer->next;
		}
		if (lexer && lexer->token == PIPE)
		{
			// process_special_token()
			lexer = lexer->next;
			current = NULL;
		}
	}
	if (!head)
		head = current;
	else if (current)
	{
		current->prev = head;
		head->next = current;
		head = current;
	}
	return (head);
}

void	parser(t_global *global)
{
	t_lexer		*token_list;
	t_command	*command_list;

	token_list = NULL;
	token_list = tokenize(global->input);
	command_list = tokens_to_commands(token_list);
	free_lexer(token_list);
	free(command_list);
}
