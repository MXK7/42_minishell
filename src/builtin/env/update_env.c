/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpoussie <mpoussie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 05:50:11 by mpoussie          #+#    #+#             */
/*   Updated: 2024/02/07 05:50:23 by mpoussie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	update_env(t_global *global, const char *env_name, const char *new_env)
{
	int		i;
	char	*temp;

	i = 0;
	while (global->env[i])
	{
		if (ft_strncmp(global->env[i], env_name, ft_strlen(env_name)) == 0)
		{
			free(global->env[i]);
			temp = ft_strjoin(env_name, new_env);
			global->env[i] = ft_strdup(temp);
			free(temp);
		}
		i++;
	}
}
