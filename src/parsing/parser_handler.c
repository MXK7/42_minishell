/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arazzok <arazzok@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/29 19:45:54 by arazzok           #+#    #+#             */
/*   Updated: 2024/01/03 17:31:04 by arazzok          ###   ########.fr       */
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
    if (lexer->token == LEFT || lexer->token == DOUBLE_LEFT)
    {
        command->redirections = malloc(sizeof(t_lexer));
        ft_memcpy(command->redirections, lexer->prev, sizeof(t_lexer));
        command->redirections->next = malloc(sizeof(t_lexer));
        ft_memcpy(command->redirections->next, lexer, sizeof(t_lexer));
        command->redirections->next->next = NULL;
        command->redirections->next->prev = command->redirections;
    }
    else if (lexer->token == RIGHT || lexer->token == DOUBLE_RIGHT)
    {
        command->redirections = malloc(sizeof(t_lexer));
        ft_memcpy(command->redirections, lexer, sizeof(t_lexer));
        command->redirections->next = malloc(sizeof(t_lexer));
        ft_memcpy(command->redirections->next, lexer->next, sizeof(t_lexer));
        command->redirections->next->next = NULL;
        command->redirections->next->prev = command->redirections;
    }
    del_one(&lexer);
}

void	handle_token(t_lexer *lexer, t_command *command)
{
	if (is_redirection(lexer->token))
        handle_redirection(lexer, command);
	else if (lexer->token == WORD)
		handle_words(lexer->str, command);
}
