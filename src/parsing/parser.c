/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arazzok <arazzok@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 21:50:36 by mpoussie          #+#    #+#             */
/*   Updated: 2024/01/02 15:59:55 by arazzok          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/// Test func
void	print_command(t_command *command)
{
	t_lexer	*redirection;

	if (!command)
	{
		printf("Command is NULL\n");
		return ;
	}
	printf("Command:\n");
	printf("  Builtin: %p\n", (void *)command->builtin);
	printf("  Num Redirections: %d\n", command->nb_redirections);
	printf("  Heredoc File Name: %s\n",
		command->heredoc_file_name ? command->heredoc_file_name : "(null)");
	printf("  Redirections:\n");
	redirection = command->redirections;
	while (redirection)
	{
		printf("    Token: %d, Value: %s\n", redirection->token,
			redirection->str);
		redirection = redirection->next;
	}
	printf("  Arguments:\n");
	for (int i = 0; i < command->nb_redirections; ++i)
		printf("    %s\n", command->str[i]);
	printf("End of Command\n");
}
///

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
		if (!head)
			head = current;
		else if (current)
		{
			current->prev = head;
			head->next = current;
			head = current;
		}
		if (lexer && lexer->token == PIPE)
			lexer = lexer->next;
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
