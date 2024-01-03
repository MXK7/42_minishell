/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arazzok <arazzok@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/29 19:45:54 by arazzok           #+#    #+#             */
/*   Updated: 2024/01/03 12:50:25 by arazzok          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    handle_words(char *word, t_command *command)
{
    int current_size;
    int new_size;
    
    current_size = get_str_size(command->str);
    new_size = current_size + 2;
    command->str = realloc(command->str, sizeof(char *) * new_size);
    if (!command->str)
        return ;
    command->str[current_size] = ft_strdup(word);
    command->str[new_size - 1] = NULL;
}

void    handle_redirection(t_lexer *lexer, t_command *command)
{
    (void)lexer;
    (void)command;
}

void	handle_token(t_lexer *lexer, t_command *command)
{
	if (lexer->token == WORD)
		handle_words(lexer->str, command);
	else if (is_redirection(lexer->token))
        handle_redirection(lexer, command);
}
