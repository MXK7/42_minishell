/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpoussie <mpoussie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 05:49:32 by mpoussie          #+#    #+#             */
/*   Updated: 2024/02/07 05:50:55 by mpoussie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	add_env_res(t_global *global, int i, char **result);

void	add_env(t_global *global, char *new_var)
{
	char	**result;
	size_t	i;
	size_t	x;

	x = 0;
	i = 0;
	while (global->env[i] != NULL)
		i++;
	result = (char **)malloc(sizeof(char *) * (i + 2));
	if (!result)
		return ;
	while (x < i)
	{
		result[x] = ft_strdup(global->env[x]);
		if (!result[x])
		{
			free_array(result);
			return ;
		}
		x++;
	}
	result[i] = ft_strdup(new_var);
	result[i + 1] = NULL;
	add_env_res(global, i, result);
}

static void	add_env_res(t_global *global, int i, char **result)
{
	if (!result[i])
	{
		free_array(result);
		return ;
	}
	free_array(global->env);
	global->env = result;
}
