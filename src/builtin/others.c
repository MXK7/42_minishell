/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   others.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpoussie <mpoussie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 01:23:21 by mpoussie          #+#    #+#             */
/*   Updated: 2023/12/15 14:11:02 by mpoussie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	_builtin_others(t_global *global)
{
	pid_t	pid;
	int		status;
	int		nbr_str;

	global->argv = split_string(global->input, &nbr_str);
	if (exe_commands(global))
	{
		pid = fork();
		if (pid == 0)
		{
			execve(global->path, global->argv, global->env);
			exit(0);
		}
		waitpid(pid, &status, 0);
		if (status != 0)
			ft_printf("STATUS : %d\n", status / 256);
	}
	else
		ft_printf("ERROR\n");
}
