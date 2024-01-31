/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   others.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arazzok <arazzok@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 01:23:21 by mpoussie          #+#    #+#             */
/*   Updated: 2024/01/31 23:01:27 by arazzok          ###   ########.fr       */
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
        if (pid < 0)
            handle_error(5, global);
		if (pid == 0)
		{
			if (global->command_list->redirections)
			{
				if (handle_redirection(global->command_list))
					exit(1);
			}
			execve(global->path, global->command_list->str, global->env);
			exit(-1);
		}
		waitpid(pid, &status, 0);
	}
	else
		ft_printf("ams: command not found: %s\n", global->command_list->str[0]);
}
