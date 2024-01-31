/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   others.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arazzok <arazzok@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 01:23:21 by mpoussie          #+#    #+#             */
/*   Updated: 2024/01/31 14:46:30 by arazzok          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	_builtin_others(t_global *global)
{
	pid_t	pid;
	int		status;

	status = 0;
	if (exe_commands(global))
	{
		pid = fork();
		if (pid == 0)
		{
			handle_redirection(global);
			execve(global->path, global->command_list->str, global->env);
			exit(-1);
		}
		waitpid(pid, &status, 0);
		if (status != 0)
			ft_printf("STATUS : %d\n", status / 256);
	}
	else
		ft_printf("ams: command not found: %s\n", global->command_list->str[0]);
}
