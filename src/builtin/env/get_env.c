/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpoussie <mpoussie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 05:48:41 by mpoussie          #+#    #+#             */
/*   Updated: 2024/02/07 05:58:18 by mpoussie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_env(char *env_name, t_global *global)
{
	char	*res;
	char	*equal_sign;
	size_t	index_env;

	res = NULL;
	if (en_len == ft_strlen(env_name))
	{
		ft_printf(ERROR_ENV_VAR);
		return (NULL);
	}
	index_env = 0;
	while (global->env[index_env])
	{
		if (!ft_strncmp(env_name, global->env[index_env], ft_strlen(env_name)
				- 1))
		{
			equal_sign = ft_strchr(global->env[index_env], '=');
			if (equal_sign != NULL)
				res = ft_strdup(equal_sign + 1);
			else
				res = NULL;
		}
		index_env++;
	}
	return (res);
}
