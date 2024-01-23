/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arazzok <arazzok@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 16:11:57 by mpoussie          #+#    #+#             */
/*   Updated: 2024/01/23 13:24:31 by arazzok          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	_env(t_global *global, char **envp)
{
	int	i;
	int	j;

	i = 0;
	while (envp[i])
		i++;
	global->env = malloc(sizeof(char **) * (i + 1));
	if (global->env == NULL)
		return ;
	j = 0;
	while (j < i)
	{
		global->env[j] = ft_strdup(envp[j]);
		j++;
	}
	global->env[j + 1] = NULL;
	i = 0;
	while (global->env[i])
	{
		if (global->env[i][0] == 'P' && global->env[i][1] == 'A'
			&& global->env[i][2] == 'T' && global->env[i][3] == 'H')
			global->path = global->env[i];
		i++;
	}
	global->pwd = getcwd(NULL, 0);
}

int	_builtin_env(t_global *global)
{
	int	i;

	i = 0;
	while (global->env[i] != NULL)
	{
		ft_putstr_fd(global->env[i], STDOUT_FILENO);
		ft_putstr_fd("\n", STDOUT_FILENO);
		i++;
	}
	return (0);
}
