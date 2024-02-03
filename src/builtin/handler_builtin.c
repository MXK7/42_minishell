/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler_builtin.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arazzok <arazzok@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 21:44:54 by mpoussie          #+#    #+#             */
/*   Updated: 2024/02/03 17:48:19 by arazzok          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	is_env_builtin(t_global *global)
{
	if (ft_strcmp(global->command_list->str[0], "cd") == 0)
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
	if (ft_strcmp(global->command_list->str[0], "echo") == 0)
		return (true);
	else if (ft_strcmp(global->command_list->str[0], "pwd") == 0)
		return (true);
	else if (ft_strcmp(global->command_list->str[0], "env") == 0)
		return (true);
	else
		return (false);
}

static void	_builtin_exe(t_global *global)
{
	if (ft_strcmp(global->command_list->str[0], "exit") == 0)
		_builtin_exit(global);
	else if (ft_strcmp(global->command_list->str[0], "pwd") == 0)
		_builtin_pwd(global);
	else if (ft_strcmp(global->command_list->str[0], "env") == 0)
		_builtin_env(global);
	else if (ft_strcmp(global->command_list->str[0], "echo") == 0)
		_builtin_echo(global);
	else if (ft_strcmp(global->command_list->str[0], "cd") == 0)
		_builtin_cd(global);
	else if (ft_strcmp(global->command_list->str[0], "export") == 0)
		_builtin_export(global);
	else if (ft_strcmp(global->command_list->str[0], "unset") == 0)
		_builtin_unset(global);
}

void	handle_command(t_global *global)
{
	if (global->command_list->redirections)
	{
		if (handle_redirection(global->command_list))
			exit(1);
	}
	if (is_builtin(global)) {
		_builtin_exe(global);
        exit(0);
    }
	if (exe_commands(global))
    {
		execve(global->path, global->command_list->str, global->env);
        exit(0);
    }
	else
    {
		ft_printf("ams: command not found: %s\n", global->command_list->str[0]);
	    exit(127);
    }
}

void	single_command(t_global *global)
{
	int	pid;
	int	status;

	call_expander(global);
	if (is_env_builtin(global))
	{
		_builtin_exe(global);
		return ;
	}
	handle_heredoc(global);
	pid = fork();
	if (pid < 0)
		handle_error(5, global);
	if (pid == 0)
		handle_command(global);
	waitpid(pid, &status, 0);
}
