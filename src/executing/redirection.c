/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arazzok <arazzok@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 14:45:38 by arazzok           #+#    #+#             */
/*   Updated: 2024/01/31 16:45:50 by arazzok          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_outfile(t_lexer *redirections, bool is_append)
{
	char	*pathname;
	int		fd;

	pathname = redirections->str;
	if (is_append)
		fd = open(pathname, O_CREAT | O_RDWR | O_APPEND, 0644);
	else
		fd = open(pathname, O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (fd < 0)
	{
		ft_putstr_fd("ams: outfile: error\n", STDERR_FILENO);
		return (1);
	}
	if (dup2(fd, STDOUT_FILENO) < 0)
	{
		ft_putstr_fd("ams: dup2 error\n", STDERR_FILENO);
		return (1);
	}
	close(fd);
	return (0);
}

int	handle_infile(t_lexer *redirections)
{
	char	*pathname;
	int		fd;

	pathname = redirections->str;
	fd = open(pathname, O_RDONLY);
	if (fd < 0)
	{
		ft_putstr_fd("ams: infile: no such file or directory\n", STDERR_FILENO);
		return (1);
	}
	if (dup2(fd, STDIN_FILENO) < 0)
	{
		ft_putstr_fd("ams: dup2 error\n", STDERR_FILENO);
		return (1);
	}
	close(fd);
	return (0);
}

int	handle_heredoc(t_lexer *redirections)
{
	(void)redirections;
	ft_printf("handle heredoc\n");
	return (0);
}
int	handle_redirection(t_global *global)
{
	t_lexer	*redirections;

	redirections = global->command_list->redirections;
	if (redirections->token == LEFT)
	{
		if (handle_infile(redirections))
			return (1);
	}
	else if (redirections->token == DOUBLE_LEFT)
	{
		if (handle_heredoc(redirections))
			return (1);
	}
	else if (redirections->token == RIGHT)
	{
		if (handle_outfile(redirections, false))
			return (1);
	}
	else if (redirections->token == DOUBLE_RIGHT)
	{
		if (handle_outfile(redirections, true))
			return (1);
	}
	return (0);
}
