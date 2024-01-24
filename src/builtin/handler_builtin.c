/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler_builtin.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpoussie <mpoussie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 21:44:54 by mpoussie          #+#    #+#             */
/*   Updated: 2024/01/24 02:39:39 by mpoussie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	_builtin_exe(t_global *global);
static bool	builtin_exist(t_global *global);

void	single_command(t_global *global)
{
	if (builtin_exist(global))
		_builtin_exe(global);
	else
		_builtin_others(global);
}

bool	builtin_exist(t_global *global)
{
	if (ft_strcmp(global->command_list->str[0], "echo") == 0)
		return (true);
	else if (ft_strcmp(global->command_list->str[0], "cd") == 0)
		return (true);
	else if (ft_strcmp(global->command_list->str[0], "pwd") == 0)
		return (true);
	else if (ft_strcmp(global->command_list->str[0], "env") == 0)
		return (true);
	else if (ft_strcmp(global->command_list->str[0], "export") == 0)
		return (true);
	else if (ft_strcmp(global->command_list->str[0], "unset") == 0)
		return (true);
	else if (ft_strcmp(global->command_list->str[0], "exit") == 0)
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
