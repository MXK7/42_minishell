/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_builtin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpoussie <mpoussie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/28 08:50:55 by mpoussie          #+#    #+#             */
/*   Updated: 2023/12/28 08:56:54 by mpoussie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	update_var(t_global *global, const char *env_name,
				const char *new_env);

char	*_env_get(char *env_name, t_global *global)
{
	size_t	en_len;
	size_t	i;

	en_len = ft_strlen(env_name);
	if (en_len == 0)
		return (NULL);
	i = 0;
	while (global->env[i])
	{
		if (!ft_strncmp(env_name, global->env[i], en_len - 1))
			return (global->env[i] + en_len + 1);
		i++;
	}
	return (NULL);
}

void	_env_update(t_global *global, const char *env_name, const char *new_env)
{
	if (env_name[0] == 'P' && env_name[1] == 'W' && env_name[2] == 'D'
		&& env_name[3] == '=')
		update_var(global, "PWD=", getcwd(NULL, 0));
	else
		update_var(global, env_name, new_env);
}

static void	update_var(t_global *global, const char *env_name,
		const char *new_env)
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

int	_env_len(char **env)
{
	int	i;

	i = 0;
	while (env[i])
		i++;
	return (i);
}
