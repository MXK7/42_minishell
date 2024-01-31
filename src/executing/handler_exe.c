/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler_exe.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arazzok <arazzok@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 13:33:54 by mpoussie          #+#    #+#             */
/*   Updated: 2024/01/31 17:26:24 by arazzok          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*make_absolute_path(const char *path, const char *exec_name);

void	get_path_exe(t_global *global)
{
	int		i;
	char	*token;

	i = 0;
	global->args_path = (char **)malloc(sizeof(char **) * ft_strlen(global->path
			+ 1));
	token = strtok(global->path + 1, ":");
	while (token != NULL)
	{
		global->args_path[i] = (char *)malloc(ft_strlen(token) + 2);
		ft_strcpy(global->args_path[i], token);
		ft_strcat(global->args_path[i], "/");
		token = strtok(NULL, ":");
		i++;
	}
	global->args_path[i] = NULL;
}

bool	exe_commands(t_global *global)
{
	int	tmp;

	global->path = ft_strdup(global->command_list->str[0]);
	if (access(global->path, X_OK) == 0)
		return (true);
	free(global->path);
	global->path = make_absolute_path(global->pwd,
		global->command_list->str[0]);
	if (access(global->path, X_OK) == 0)
		return (true);
	free(global->path);
	global->path = NULL;
	tmp = global->nbr_path;
	while (tmp > 0)
	{
		// ! Cette ligne fait leak ls
		global->path = ft_strjoin(global->args_path[tmp - 1],
			global->command_list->str[0]);
		// !
		if (access(global->path, X_OK) == 0)
			return (true);
		free(global->path);
		global->path = NULL;
		tmp--;
	}
	return (false);
}

static char	*make_absolute_path(const char *path, const char *exec_name)
{
	char	*absolute_path;
	size_t	path_length;
	size_t	exec_name_length;

	if (!path || !exec_name)
	{
		exit(-1);
		return (NULL);
	}
	path_length = ft_strlen(path);
	exec_name_length = ft_strlen(exec_name);
	absolute_path = (char *)malloc(path_length + 1 + exec_name_length + 1);
	if (absolute_path == NULL)
		return (NULL);
	ft_memcpy(absolute_path, path, path_length);
	absolute_path[path_length] = '/';
	ft_memcpy(absolute_path + path_length + 1, path, exec_name_length);
	absolute_path[exec_name_length + 1 + path_length] = '\0';
	return (absolute_path);
}
