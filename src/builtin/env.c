/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpoussie <mpoussie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 16:11:57 by mpoussie          #+#    #+#             */
/*   Updated: 2024/02/02 16:06:17 by mpoussie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void init_env(t_global *global, char **envp)
{
	int	i;
	int	j;

	i = 0;
	while (envp[i])
		i++;
	global->env = calloc(1, sizeof(char **) * (i + 1));
	if (global->env == NULL)
		return ;
	j = 0;
	while (j < i)
	{
		global->env[j] = ft_strdup(envp[j]);
		j++;
	}
	global->env[j] = NULL;
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
