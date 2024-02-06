/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_builtin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpoussie <mpoussie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/28 08:50:55 by mpoussie          #+#    #+#             */
/*   Updated: 2024/02/06 15:31:50 by mpoussie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_env(char *env_name, t_global *global)
{
	char	*res;
	char	*equal_sign;
	size_t	en_len;
	size_t	index_env;

	en_len = ft_strlen(env_name);
	if (en_len == 0)
	{
		ft_printf("Error code: 1, var en_len");
		return (NULL);
	}
	index_env = 0;
	while (global->env[index_env])
	{
		if (!ft_strncmp(env_name, global->env[index_env], en_len - 1))
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

size_t	tab_len(char **tab)
{
	size_t	i;

	if (!tab)
		return (0);
	i = 0;
	while (tab[i])
		i++;
	return (i);
}
