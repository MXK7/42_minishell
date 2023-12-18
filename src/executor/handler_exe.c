/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler_exe.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpoussie <mpoussie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 13:33:54 by mpoussie          #+#    #+#             */
/*   Updated: 2023/12/18 20:21:54 by mpoussie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	while (global->nbr_path > 0)
	{
		global->path = ft_strjoin(global->args_path[global->nbr_path - 1],
				global->argv[0]);
		if (access(global->path, X_OK) == 0)
			return (true);
		global->nbr_path--;
	}
	return (false);
}
