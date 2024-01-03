/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arazzok <arazzok@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 21:50:36 by mpoussie          #+#    #+#             */
/*   Updated: 2024/01/03 12:47:45 by arazzok          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/// Test func
void	print_command(t_command *command)
{
	int i;
	t_lexer	*redirection;

	if (!command)
	{
		printf("Command is NULL\n");
		return ;
	}
	printf("Command:\n");
	printf("  Words:\n");
	i = 0;
	while (command->str[i]) {
		printf("    %s\n", command->str[i]);
		i++;
	}
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
	ft_bzero(node, sizeof(t_command));
	node->str = (char **) malloc(1 * sizeof(char *));
	if (!node->str)
		return (free(node), NULL);
	node->str[0] = NULL;
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
		printf("TOKEN STR: %s\n", lexer->str);
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
	print_command(command_list);
	free_lexer(token_list);
	free(command_list);
}
