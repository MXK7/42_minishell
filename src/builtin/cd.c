/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpoussie <mpoussie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 10:18:31 by mpoussie          #+#    #+#             */
/*   Updated: 2024/02/07 17:47:56 by mpoussie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	open_cd(char *dir, t_global *global, bool _free);

int	_builtin_cd(t_global *global)
{
	int	i;

	global->old_pwd = global->pwd;
	global->pwd = getcwd(NULL, 1024);
	i = 0;
	while (global->command_list->str[i])
		i++;
	if (i > 2)
	{
		ft_printf(ERROR_CD_ARGS);
		return (1);
	}
	if (i == 1)
		open_cd(get_env("HOME", global), global, true);
	else if (ft_strcmp(global->command_list->str[1], "-") == 0)
		open_cd(get_env("OLDPWD", global), global, true);
	else if (global->command_list->str[1] != NULL)
		open_cd(global->command_list->str[1], global, false);
	return (0);
}

static int	open_cd(char *dir, t_global *global, bool _free)
{
	char	*str;

	if (chdir(dir) == 0)
	{
		str = getcwd(NULL, 1024);
		update_env(global, "PWD=", str);
		update_env(global, "OLDPWD=", global->old_pwd);
		if (_free)
			free(dir);
	}
	return (0);
}
