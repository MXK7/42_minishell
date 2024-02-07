/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler_exe.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpoussie <mpoussie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 13:33:54 by mpoussie          #+#    #+#             */
/*   Updated: 2024/02/07 03:56:06 by mpoussie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*make_absolute_path(const char *path, const char *exec_name);
static bool	exe_path(t_global *global);

void	get_path_exe(t_global *global)
{
	int		i;
	char	**token;

	i = 0;
	token = NULL;
	global->path = get_env("PATH=", global);
	
	if (global->path != NULL)
	{
		global->nbr_path = count_path(global->path);
		global->args_path = (char **)malloc(sizeof(char **) * (ft_strlen(global->path) + 1));
		token = ft_split(global->path, ':');
		while (token[i] != NULL)
		{
			global->args_path[i] = (char *)malloc(ft_strlen(token[i]) + 2);
			ft_strcpy(global->args_path[i], token[i]);
			ft_strcat(global->args_path[i], "/");
			i++;
		}
		free_array(token);
		global->args_path[i] = NULL;
	}
	else
	{
		global->nbr_path = 0;
		global->args_path = NULL;
	}
}

bool	exe_commands(t_global *global)
{
	if (ft_strlen(global->command_list->str[0]) == 1)
		return (false);
	free(global->path);
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
	if (ft_strchr(global->command_list->str[0], '/') == NULL 
		&& exe_path(global))
		return (true);
	return (false);
}

static bool	exe_path(t_global *global)
{
	int	tmp;

	get_path_exe(global);
	
	tmp = global->nbr_path;
	while (tmp > 0)
	{
		global->path = ft_strjoin(global->args_path[tmp - 1],
				global->command_list->str[0]);
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
