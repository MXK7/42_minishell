/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler_builtin.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpoussie <mpoussie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 21:44:54 by mpoussie          #+#    #+#             */
/*   Updated: 2024/02/07 17:04:22 by mpoussie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	is_env_builtin(t_global *global)
{
	if (!global->command_list->str[0])
		return (false);
	else if (ft_strcmp(global->command_list->str[0], "cd") == 0)
		return (true);
	else if (ft_strcmp(global->command_list->str[0], "exit") == 0)
		return (true);
	else if (ft_strcmp(global->command_list->str[0], "export") == 0)
		return (true);
	else if (ft_strcmp(global->command_list->str[0], "unset") == 0)
		return (true);
	else
		return (false);
}

static bool	is_builtin(t_global *global)
{
	if (!global->command_list->str[0])
		return (false);
	else if (ft_strcmp(global->command_list->str[0], "echo") == 0)
		return (true);
	else if (ft_strcmp(global->command_list->str[0], "pwd") == 0)
		return (true);
	else if (ft_strcmp(global->command_list->str[0], "env") == 0)
		return (true);
	else
		return (false);
}

static int	_builtin_exe(t_global *global)
{
	int	status;

	status = 0;
	if (ft_strcmp(global->command_list->str[0], "exit") == 0)
		status = _builtin_exit(global);
	else if (ft_strcmp(global->command_list->str[0], "pwd") == 0)
		status = _builtin_pwd(global);
	else if (ft_strcmp(global->command_list->str[0], "env") == 0)
		status = _builtin_env(global);
	else if (ft_strcmp(global->command_list->str[0], "echo") == 0)
		status = _builtin_echo(global);
	else if (ft_strcmp(global->command_list->str[0], "cd") == 0)
		status = _builtin_cd(global);
	else if (ft_strcmp(global->command_list->str[0], "export") == 0)
		status = _builtin_export(global);
	else if (ft_strcmp(global->command_list->str[0], "unset") == 0)
		status = _builtin_unset(global);
	return (status);
}

void	handle_command(t_global *global)
{
	int	exit_status;

	exit_status = 0;
	if (global->command_list->redirections)
	{
		if (handle_redirection(global->command_list))
			exit(1);
	}
	if (!global->command_list->str[0])
	{
		free_global(global);
		exit(exit_status);
	}
	if (is_builtin(global))
		_builtin_exe(global);
	else if (exe_commands(global))
		execve(global->path, global->command_list->str, global->env);
	else
	{
		ft_printf("ams: command not found: %s\n", global->command_list->str[0]);
		exit_status = 127;
	}
	free_global(global);
	exit(exit_status);
}

void	single_command(t_global *global)
{
	int	pid;
	int	status;

	if (is_env_builtin(global))
	{
		g_exit_status = _builtin_exe(global);
		return ;
	}
	handle_heredoc(global, global->command_list);
	signal(SIGINT, handle_sigint_cmd);
	signal(SIGQUIT, handle_sigquit);
	pid = fork();
	if (pid < 0)
		handle_error(5, global);
	if (pid == 0)
		handle_command(global);
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		g_exit_status = WEXITSTATUS(status);
}
