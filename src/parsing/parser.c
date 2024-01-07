/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arazzok <arazzok@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 21:50:36 by mpoussie          #+#    #+#             */
/*   Updated: 2024/01/07 23:49:48 by arazzok          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/// ***** TEST FUNCTIONS START ***** ///
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
/// ***** TEST FUNCTIONS END ***** ///

t_lexer	*tokenize(char *input)
{
	t_lexer	*head;
	t_lexer	*current;
	int		len;
	int		i;

	head = NULL;
	current = NULL;
	len = ft_strlen(input);
	i = 0;
	while (i < len)
	{
		skip_whitespaces(input, &i);
		if (is_operator(input[i]))
			handle_operator(input, &i, &current, input[i]);
		else if (is_quote(input[i]))
			handle_quote(input, &i, &current, input[i]);
		else
			handle_word(input, &i, &current);
		handle_head(&head, current);
		i++;
	}
	return (head);
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
    command_list = NULL;
	command_list = tokens_to_commands(token_list);
	print_command_list(command_list);
	free_lexer(&token_list);
    // TODO: free command list
}
