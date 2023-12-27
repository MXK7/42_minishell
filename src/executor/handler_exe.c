/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler_exe.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpoussie <mpoussie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 13:33:54 by mpoussie          #+#    #+#             */
/*   Updated: 2023/12/27 08:41:24 by mpoussie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*make_absolute_path(const char *path, const char *exec_name);

void	handler_exe(t_global *global)
{
	int		i;
	char	*token;
	char	*path_start;
	size_t	token_len;

	path_start = ft_strchr(global->path, '=');
	if (path_start == NULL)
	{
		ft_printf(ERROR_PATH_EGAL);
		return ;
	}
	i = 0;
	global->args_path = (char **)malloc(sizeof(char *) * ft_strlen(path_start
			+ 1));
	token = strtok(path_start + 1, ":");
	while (token != NULL)
	{
		token_len = ft_strlen(token);
		global->args_path[i] = (char *)malloc(token_len + 2);
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

	global->path = ft_strdup(global->argv[0]);
	if (access(global->path, X_OK) == 0)
		return (true);
	free(global->path);
	global->path = make_absolute_path(global->pwd, global->argv[0]);
	if (access(global->path, X_OK) == 0)
		return (true);
	free(global->path);
	tmp = global->nbr_path;
	while (tmp > 0)
	{
		global->path = ft_strjoin(global->args_path[tmp - 1], global->argv[0]);
		if (access(global->path, X_OK) == 0)
			return (true);
		free(global->path);
		tmp--;
	}
	return (false);
}

static char	*make_absolute_path(const char *path, const char *exec_name)
{
	char	*absolute_path;
	size_t	path_length;
	size_t	exec_name_length;

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
