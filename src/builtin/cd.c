/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpoussie <mpoussie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 10:18:31 by mpoussie          #+#    #+#             */
/*   Updated: 2024/02/05 12:38:04 by mpoussie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	open_cd(int fd, char *dir, t_global *global);

int	_builtin_cd(t_global *global)
{
	int	fd;
	int	i;

	global->old_pwd = global->pwd;
	global->pwd = getcwd(NULL, 0);
	fd = 0;
	i = 0;
	while (global->command_list->str[i])
		i++;
	if (i > 2)
	{
		ft_printf("CD: There are too many arguments.\n");
		return (1);
	}
	if (i == 1)
		open_cd(fd, get_env("HOME=", global), global);
	else if (ft_strcmp(global->command_list->str[1], "-") == 0)
		open_cd(fd, get_env("OLDPWD=", global), global);
	else if (global->command_list->str[1] != NULL)
		open_cd(fd, global->command_list->str[1], global);
	return (0);
}

static int	open_cd(int fd, char *dir, t_global *global)
{
	if (opendir(dir) != NULL)
	{
		fd = open(dir, O_RDONLY);
		if (fd == -1)
		{
			return (1);
		}
		close(fd);
	}
	if (chdir(dir) == 0)
	{
		update_env(global, "PWD=", getcwd(NULL, 0));
		update_env(global, "OLDPWD=", global->old_pwd);
	}
	return (0);
}
