/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arazzok <arazzok@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 18:23:53 by arazzok           #+#    #+#             */
/*   Updated: 2024/01/23 12:41:27 by arazzok          ###   ########.fr       */
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
	(void)lexer_list;
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
	reset_global(global);
	return (1);
}

int	handle_error(int err_code, t_global *global)
{
	ft_putstr_fd("Error.\n", STDERR_FILENO);
	if (err_code == 0)
		ft_putendl_fd("Syntax error near unexpected token 'newline'.",
			STDERR_FILENO);
	else if (err_code == 1)
		ft_putendl_fd("Memory allocation error.", STDERR_FILENO);
	else if (err_code == 2)
		ft_putendl_fd("Quotes are note closed.", STDERR_FILENO);
    else if (err_code == 3)
		ft_putendl_fd("Parser error.", STDERR_FILENO);
    else if (err_code == 4)
		ft_putendl_fd("Failed to create pipe.", STDERR_FILENO);
    else if (err_code == 5)
		ft_putendl_fd("Failed to fork.", STDERR_FILENO);
    else if (err_code == 6)
		ft_putendl_fd("Outfile error.", STDERR_FILENO);
    else if (err_code == 7)
		ft_putendl_fd("Infile: No such file or directory.", STDERR_FILENO);
    else if (err_code == 8)
		ft_putendl_fd("Path does not exist.", STDERR_FILENO);
	reset_global(global);
	return (1);
}
