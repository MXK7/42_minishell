/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   others.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpoussie <mpoussie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 01:23:21 by mpoussie          #+#    #+#             */
/*   Updated: 2023/12/11 14:50:28 by mpoussie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	_builtin_others(t_global *global)
{
	pid_t	pid;
	int		status;
	int		i;
	int		nbr_path;
	char	*token;
	int		x;

	status = 0;
	pid = fork();
	nbr_path = count_path(global->path);
	global->args_path = malloc(sizeof(char *) * (nbr_path + 1));
	if (global->args_path == NULL)
		exit(0);
	i = 0;
	token = strtok(global->path, ":");
	while (token != NULL)
	{
		// if (ft_strncmp(token, "PATH=/home/mpoussie/bin", 23) == 0)
		// global->args_path[i++] = ft_strdup(token + 23);
		// else
		global->args_path[i++] = ft_strdup(token);
		token = strtok(NULL, ":");
	}
	global->args_path[i] = NULL;
	if (pid == 0)
	{
		x = 0;
		while (global->args_path[x] != NULL)
		{
			printf("%s\n", global->args_path[x]);
			x++;
		}
		printf("global->path: %s\n", global->path);
		execve(global->args_path[0], global->args_path, global->env);
		exit(0);
	}
	waitpid(pid, &status, 0);
}
