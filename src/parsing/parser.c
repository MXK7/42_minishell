/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arazzok <arazzok@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 21:50:36 by mpoussie          #+#    #+#             */
/*   Updated: 2024/01/03 17:29:20 by arazzok          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/// *** TEST FUNCTIONS START *** ///
static void	print_command(t_command *command)
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

static void	print_command_list(t_command *head)
{
	t_command	*current;

	current = head;
	while (current)
	{
		print_command(current);
		current = current->next;
	}
}
/// *** TEST FUNCTIONS END *** ///

t_command	*init_command(void)
{
	t_command	*node;

	node = malloc(sizeof(t_command));
	if (!node)
		return (NULL);
	ft_bzero(node, sizeof(t_command));
	node->str = (char **) malloc(sizeof(char *));
	if (!node->str)
		return (free(node), NULL);
	node->str[0] = NULL;
	return (node);
}

static void	handle_cmd_head(t_command **head, t_command *current)
{
	t_command	*temp;

	if (*head == NULL)
		*head = current;
	else
	{
		temp = *head;
		while (temp->next)
			temp = temp->next;
		temp->next = current;
		current->prev = temp;
		current->next = NULL;
	}
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
			lexer = lexer->next;
		handle_cmd_head(&head, current);
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
	print_command_list(command_list);
	free_lexer(token_list);
	free(command_list);
}
