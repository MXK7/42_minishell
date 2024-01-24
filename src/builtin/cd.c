/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpoussie <mpoussie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 10:18:31 by mpoussie          #+#    #+#             */
/*   Updated: 2024/01/24 03:02:06 by mpoussie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	_builtin_cd(t_global *global)
{
	char	*new_pwd;
	int		fd;

	if (opendir(global->command_list->str[1]) != NULL)
	{
		fd = open(global->command_list->str[1], O_RDONLY);
		if (fd == -1)
		{
			printf("ERROR CD OPEN\n");
			close(fd);
			return (1);
		}
		close(fd);
	}
	if (chdir(global->command_list->str[1]) == 0)
	{
		new_pwd = ft_strjoin(get_env("PWD=", global), ft_strjoin("/", global->command_list->str[1]));
		_env_update(global, "PWD=", new_pwd);
	}
	else
		printf("ERROR CD\n");
	return (0);
}
