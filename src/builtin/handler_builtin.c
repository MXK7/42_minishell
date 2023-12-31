/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler_builtin.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpoussie <mpoussie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 21:44:54 by mpoussie          #+#    #+#             */
/*   Updated: 2023/12/08 21:34:52 by mpoussie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	builtin_start(t_global *global, char **envp)
{
	_env(global, envp);
}

bool	builtin_exist(t_global *global)
{
	if (ft_strcmp(global->input, "echo") == 0)
		return (true);
	else if (ft_strcmp(global->input, "cd") == 0)
		return (true);
	else if (ft_strcmp(global->input, "pwd") == 0)
		return (true);
	else if (ft_strcmp(global->input, "env") == 0)
		return (true);
	else if (ft_strcmp(global->input, "export") == 0)
		return (true);
	else if (ft_strcmp(global->input, "unset") == 0)
		return (true);
	else if (ft_strcmp(global->input, "exit") == 0)
		return (true);
	else
		return (false);
}

void	handler_builtin(t_settings *settings, t_global *global)
{
	if (builtin_exist(global))
	{
		if (ft_strcmp(global->input, "exit") == 0)
			settings->exitRequested = false;
		else if (ft_strcmp(global->input, "pwd") == 0)
			_builtin_pwd(global);
		else if (ft_strcmp(global->input, "env") == 0)
			_builtin_env(global);
	}
	else
		_builtin_others(global);
}
