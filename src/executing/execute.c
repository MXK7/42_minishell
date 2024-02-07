/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpoussie <mpoussie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 14:51:03 by arazzok           #+#    #+#             */
/*   Updated: 2024/02/07 03:55:48 by mpoussie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	process_dup(t_global *global, int pipefd[2], int fd_in, t_command *current)
{
	if (current->prev && dup2(fd_in, STDIN_FILENO) < 0)
		handle_error(4, global);
	close(pipefd[0]);
	if (current->next && dup2(pipefd[1], STDOUT_FILENO) < 0)
		handle_error(4, global);
	close(pipefd[1]);
	if (current->prev)
		close(fd_in);
	handle_command(global);
	return (0);
}

int	process_fork(t_global *global, int pipefd[2], int fd_in, t_command *current)
{
	static int	i = 0;

	if (global->is_reset == true)
	{
		i = 0;
		global->is_reset = false;
	}
	global->pid[i] = fork();
	if (global->pid[i] < 0)
		handle_error(5, global);
	if (global->pid[i] == 0)
		process_dup(global, pipefd, fd_in, current);
	i++;
	return (0);
}

int	check_fd_heredoc(t_global *global, int pipefd[2], t_command *current)
{
	int	fd_in;

	if (global->is_heredoc)
	{
		close(pipefd[0]);
		fd_in = open(current->heredoc_file_name, O_RDONLY);
	}
	else
		fd_in = pipefd[0];
	return (fd_in);
}

int	process_waitpid(int *pid, int nb_pipes)
{
	int	i;
	int	status;

	i = 0;
	while (i < nb_pipes)
	{
		waitpid(pid[i], &status, 0);
		i++;
	}
	waitpid(pid[i], &status, 0);
	return (0);
}

int	execute(t_global *global)
{
	int	pipefd[2];
	int	fd_in;

	fd_in = STDIN_FILENO;
	while (global->command_list)
	{
		if (global->command_list->next)
			pipe(pipefd);
		handle_heredoc(global);
		signal(SIGINT, handle_sigint_cmd);
		signal(SIGQUIT, handle_sigquit);
		process_fork(global, pipefd, fd_in, global->command_list);
		close(pipefd[1]);
		if (global->command_list->prev)
			close(fd_in);
		fd_in = check_fd_heredoc(global, pipefd, global->command_list);
		if (global->command_list->next)
			global->command_list = global->command_list->next;
		else
			break ;
	}
	process_waitpid(global->pid, global->nb_pipes);
	global->command_list = command_first(global->command_list);
	return (0);
}
