/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arazzok <arazzok@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/27 08:36:51 by mpoussie          #+#    #+#             */
/*   Updated: 2024/01/23 13:31:55 by arazzok          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**_delete_var(char **env, char *env_name);

int	_builtin_unset(t_global *global)
{
	int	i;

	if (global->argv[1] == NULL)
	{
		ft_printf("unset: not enough arguments\n");
		return (1);
	}
	i = 0;
	while (global->env[i])
	{
		global->env = _delete_var(global->env, global->argv[1]);
		i++;
	}
	return (0);
}

static char	**_delete_var(char **env, char *env_name)
{
	char	**new_env;
	int		i;
	int		x;

	new_env = (char **)malloc(sizeof(char *) * _env_len(env) + 1);
	i = 0;
	x = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], ft_strtoupper(env_name),
				ft_strlen(env_name)) != 0)
		{
			new_env[x] = env[i];
			x++;
		}
		i++;
	}
	new_env[x] = 0;
	free(new_env);
	return (new_env);
}
