/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   others.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpoussie <mpoussie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 01:23:21 by mpoussie          #+#    #+#             */
/*   Updated: 2023/12/26 07:38:25 by mpoussie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	_builtin_others(t_global *global)
{
	pid_t	pid;
	int		status;

	status = 0;
	pid = fork();
	if (exe_commands(global))
	{
		if (pid == 0)
		{
			printf("global->path:%s\nglobal->argv:%s\nglobal->env:%s\n", global->path, global->argv[0], global->env[0]);
			execve(global->path, global->argv, global->env);
			exit(0);
		}
		waitpid(pid, &status, 0);
		if (status != 0)
			ft_printf("STATUS : %d\n", status / 256);
	}
}
