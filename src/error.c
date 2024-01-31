/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arazzok <arazzok@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 18:23:53 by arazzok           #+#    #+#             */
/*   Updated: 2024/01/31 23:46:51 by arazzok          ###   ########.fr       */
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
	ft_putstr_fd("ams: parse error near ", STDERR_FILENO);
	if (token == RIGHT)
		ft_putendl_fd("'>'", STDERR_FILENO);
	else if (token == DOUBLE_RIGHT)
		ft_putendl_fd("'>>'", STDERR_FILENO);
	else if (token == LEFT)
		ft_putendl_fd("'<'", STDERR_FILENO);
	else if (token == DOUBLE_LEFT)
		ft_putendl_fd("'<<'", STDERR_FILENO);
	else if (token == PIPE)
		ft_putendl_fd("'|'", STDERR_FILENO);
	else
		ft_putstr_fd("\n", STDERR_FILENO);
	free_lexer(&lexer_list);
	reset_global(global);
	return (1);
}

int	handle_error(int err_code, t_global *global)
{
	ft_putstr_fd("ams: ", STDERR_FILENO);
	if (err_code == 0)
		ft_putendl_fd("syntax error near unexpected token 'newline'",
			STDERR_FILENO);
	else if (err_code == 1)
		ft_putendl_fd("memory allocation error", STDERR_FILENO);
	else if (err_code == 2)
		ft_putendl_fd("quotes are note closed", STDERR_FILENO);
    else if (err_code == 3)
		ft_putendl_fd("parser error", STDERR_FILENO);
    else if (err_code == 4)
		ft_putendl_fd("failed to create pipe", STDERR_FILENO);
    else if (err_code == 5)
		ft_putendl_fd("failed to fork", STDERR_FILENO);
    else if (err_code == 6)
		ft_putendl_fd("outfile error", STDERR_FILENO);
    else if (err_code == 7)
		ft_putendl_fd("infile: no such file or directory", STDERR_FILENO);
    else if (err_code == 8)
		ft_putendl_fd("path does not exist", STDERR_FILENO);
	reset_global(global);
	return (1);
}
