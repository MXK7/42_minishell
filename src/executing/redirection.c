/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arazzok <arazzok@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 14:45:38 by arazzok           #+#    #+#             */
/*   Updated: 2024/01/31 23:07:11 by arazzok          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_outfile(t_lexer *redirections)
{
	char	*pathname;
	int		fd;

	pathname = redirections->str;
	if (redirections->token == DOUBLE_RIGHT)
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

int	handle_infile(char *pathname)
{
	int		fd;

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

int	handle_redirection(t_command *command)
{
	t_lexer	*start;

	start = command->redirections;
	while (command->redirections)
	{
		if (command->redirections->token == LEFT)
		{
			if (handle_infile(command->redirections->str))
				return (1);
		}
		else if (command->redirections->token == DOUBLE_LEFT)
		{
			if (handle_infile(command->heredoc_file_name))
				return (1);
		}
		else if (command->redirections->token == RIGHT
			|| command->redirections->token == DOUBLE_RIGHT)
		{
			if (handle_outfile(command->redirections))
				return (1);
		}
		command->redirections = command->redirections->next;
	}
	command->redirections = start;
	return (0);
}
