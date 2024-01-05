/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arazzok <arazzok@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/29 19:45:54 by arazzok           #+#    #+#             */
/*   Updated: 2024/01/05 18:31:07 by arazzok          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_words(char *word, t_command *command)
{
	int	current_size;
	int	new_size;

	current_size = get_str_size(command->str);
	new_size = current_size + 2;
	command->str = realloc(command->str, sizeof(char *) * new_size);
	if (!command->str)
		return ;
	command->str[current_size] = ft_strdup(word);
	command->str[new_size - 1] = NULL;
}

void	handle_redirection(t_lexer *lexer, t_command *command)
{
	t_lexer	*sign;
	t_lexer	*file_name;

	if (lexer->token == DOUBLE_LEFT || lexer->token == LEFT
		|| lexer->token == RIGHT || lexer->token == DOUBLE_RIGHT)
	{
		sign = init_lexer(lexer->str, lexer->token, lexer->index);
		file_name = init_lexer(lexer->next->str, lexer->next->token,
				lexer->next->index);
		sign->next = file_name;
		file_name->prev = sign;
		command->redirections = sign;
	    command->nb_redirections++;
	    del_one(&lexer);
	}
}

void	handle_token(t_lexer *lexer, t_command *command)
{
	if (is_redirection(lexer->token))
		handle_redirection(lexer, command);
	else if (lexer->token == WORD)
		handle_words(lexer->str, command);
}
