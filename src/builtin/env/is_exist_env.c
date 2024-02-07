/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_exist_env.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpoussie <mpoussie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 05:48:55 by mpoussie          #+#    #+#             */
/*   Updated: 2024/02/07 17:10:18 by mpoussie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_exist_env(char *env_name, t_global *global)
{
	int	i;

	i = 0;
	while (global->env[i] != NULL)
	{
		if (ft_strncmp(env_name, global->env[i], ft_strlen(env_name)) == 0)
			return (true);
		i++;
	}
	return (false);
}
