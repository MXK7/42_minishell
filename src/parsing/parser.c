/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arazzok <arazzok@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 21:50:36 by mpoussie          #+#    #+#             */
/*   Updated: 2024/01/11 18:42:27 by arazzok          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/// ***** TEST FUNCTIONS START ***** ///
static void	print_command(t_command *command)
{
	int		i;
	t_lexer	*redirection;

	if (!command)
	{
		printf("Command is NULL\n");
		return ;
	}
	printf("Command:\n");
	printf("  Words:\n");
	i = 0;
	while (command->str[i])
	{
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

t_command	*pre_init_command(t_parser *parser)
{
	char	**str;
	t_lexer	*temp;
	int		i;
	int		arg_size;

	del_redirections(parser);
	arg_size = count_args(parser->lexer_list);
	str = ft_calloc(arg_size + 1, sizeof(char *));
	if (!str)
		return (NULL);
	temp = parser->lexer_list;
	i = 0;
	while (arg_size > 0)
	{
		if (temp->str)
		{
			str[i++] = ft_strdup(temp->str);
			del_one(&parser->lexer_list, temp->index);
			temp = parser->lexer_list;
		}
		arg_size--;
	}
	return (init_command(str, parser->nb_redirections, parser->redirections));
}

int	parser(t_global *global)
{
	t_command	*command_list;
	t_parser	parser;

	count_pipes(global);
	if (global->lexer_list->token == PIPE)
	{
		ft_putendl_fd("Error.\nParse error: double token.", STDERR_FILENO);
		return (1);
	}
	while (global->lexer_list)
	{
		if (global->lexer_list && global->lexer_list->token == PIPE)
			del_one(&global->lexer_list, global->lexer_list->index);
		parser = init_parser(global);
		command_list = pre_init_command(&parser);
        // ? Gérer command_list == NULL ?
        if (!global->command_list)
            global->command_list = command_list;
        else
            push_command(&global->command_list, command_list);
        global->lexer_list = parser.lexer_list;
	}
	print_command_list(global->command_list);
	return (0);
}
