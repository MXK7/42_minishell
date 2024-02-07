/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpoussie <mpoussie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 05:52:48 by mpoussie          #+#    #+#             */
/*   Updated: 2024/02/07 17:35:01 by mpoussie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**remove_env(char **env, char *env_name)
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
