/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpoussie <mpoussie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 16:11:57 by mpoussie          #+#    #+#             */
/*   Updated: 2023/12/06 16:56:22 by mpoussie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	get_env(t_global *global, char **envp)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (envp[i])
		i++;
	global->env = (char **)malloc(sizeof(char **) * (i + 1));
	while (i > j)
	{
		global->env[j] = envp[j];
		j++;
	}
	global->env[j] = NULL;
}

int	print_env(t_global *global)
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
