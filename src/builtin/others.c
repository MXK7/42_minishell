/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   others.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpoussie <mpoussie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 01:23:21 by mpoussie          #+#    #+#             */
/*   Updated: 2024/01/23 16:54:29 by mpoussie         ###   ########.fr       */
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
			execve(global->path, global->command_list->str, global->env);
			exit(-1);
		}
		waitpid(pid, &status, 0);
		if (status != 0)
			ft_printf("STATUS : %d\n", status / 256);
	}
}
