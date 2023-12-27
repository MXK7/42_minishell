/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   others.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpoussie <mpoussie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 01:23:21 by mpoussie          #+#    #+#             */
/*   Updated: 2023/12/27 08:14:43 by mpoussie         ###   ########.fr       */
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
			execve(global->path, global->argv, global->env);
			exit(-1);
		}
		waitpid(pid, &status, 0);
		if (status != 0)
			ft_printf("STATUS : %d\n", status / 256);
	}
}
