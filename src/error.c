/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arazzok <arazzok@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 18:23:53 by arazzok           #+#    #+#             */
/*   Updated: 2024/01/18 18:30:54 by arazzok          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parser_error(int err_code, t_global *global, t_lexer *lexer_list)
{
	free_lexer(&lexer_list);
	handle_error(err_code, global);
}

int	double_token_error(t_global *global, t_lexer *lexer_list, t_token token)
{
    (void)global;
	ft_putstr_fd("Error.\nParse error near ", STDERR_FILENO);
	if (token == RIGHT)
		ft_putstr_fd("'>'\n", STDERR_FILENO);
	else if (token == DOUBLE_RIGHT)
		ft_putstr_fd("'>>'\n", STDERR_FILENO);
	else if (token == LEFT)
		ft_putstr_fd("'<'\n", STDERR_FILENO);
	else if (token == DOUBLE_LEFT)
		ft_putstr_fd("'<<'\n", STDERR_FILENO);
	else if (token == PIPE)
		ft_putstr_fd("'|'\n", STDERR_FILENO);
	else
		ft_putstr_fd("\n", STDERR_FILENO);
	free_lexer(&lexer_list);
	// free_global(global);
	return (1);
}

int	handle_error(int err_code, t_global *global)
{
	(void)global;
	ft_putstr_fd("Error.\n", STDERR_FILENO);
	if (err_code == 0)
		ft_putendl_fd("Syntax error near unexpected token 'newline'.",
			STDERR_FILENO);
	else if (err_code == 1)
		ft_putendl_fd("Quotes are note closed.", STDERR_FILENO);
	else if (err_code == 2)
		ft_putendl_fd("Memory allocation error.", STDERR_FILENO);
	// free_global(global);
	return (1);
}
