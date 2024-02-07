/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpoussie <mpoussie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/27 08:36:51 by mpoussie          #+#    #+#             */
/*   Updated: 2024/02/07 02:31:11 by mpoussie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**_delete_var(char **env, char *env_name);

int	_builtin_unset(t_global *global)
{
	int	i;

	if (global->command_list->str[1] == NULL)
	{
		ft_printf(ERROR_UNSET_ARGS);
		return (1);
	}
	i = 1;
	while (global->command_list->str[i] != NULL)
	{
		global->env = _delete_var(global->env, global->command_list->str[i]);
		i++;
	}
	return (0);
}

static char	**_delete_var(char **env, char *env_name)
{
	char	**new_env;
	int		i;
	int		x;

	new_env = (char **)malloc(sizeof(char *) * (tab_len(env) + 1));
	i = 0;
	x = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], env_name, ft_strlen(env_name)) != 0)
		{
			new_env[x] = env[i];
			x++;
		}
		else
			free(env[i]);
		i++;
	}
	new_env[x] = NULL;
	free(env);
	return (new_env);
}
