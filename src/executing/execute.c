/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpoussie <mpoussie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 14:51:03 by arazzok           #+#    #+#             */
/*   Updated: 2024/02/02 18:30:31 by mpoussie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_execute(t_global *global, char **envp)
{
	global->env = NULL;
	global->args_path = NULL;
	global->old_pwd = NULL;
	init_env(global, envp);
	global->path = get_env("PATH=", global);
	global->pwd = getcwd(NULL, 0);
	global->nbr_path = count_path(global->path);
	get_path_exe(global);
}

int	execute(t_global *global)
{
	int			pipefd[2];
	int			fd_in;
	t_command	*current;

	fd_in = STDIN_FILENO;
	current = global->command_list;
	while (current)
	{
		// TODO: expand env variables
		if (current->next)
			pipe(pipefd);
		handle_heredoc(global);
		// TODO: fork
		close(pipefd[0]);
		if (current->prev)
			close(fd_in);
		// TODO: check fd heredoc
		if (current->next)
			current = current->next;
		else
			break ;
	}
	// TODO: waitpid
	return (0);
}
