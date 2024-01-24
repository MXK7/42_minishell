/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_builtin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpoussie <mpoussie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/28 08:50:55 by mpoussie          #+#    #+#             */
/*   Updated: 2024/01/24 18:51:55 by mpoussie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	update_var(t_global *global, const char *env_name,
	const char *new_env);

char	*get_env(char *env_name, t_global *global)
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

int (*get_builtin(char *str))(t_global *global)
{
	static void *builtins[7][2] = {{"cd", _builtin_cd}, {"echo", _builtin_echo},
		{"env", _builtin_env}, {"exit", _builtin_exit}, {"export",
		_builtin_export}, {"pwd", _builtin_pwd}, {"unset", _builtin_unset}};
	int i;

	i = 0;
	while (i < 7)
	{
		if (str)
		{
			if (!ft_strncmp(builtins[i][0], str, ft_strlen(builtins[i][0])))
				return builtins[i][1];
		}
		i++;
	}
	return (NULL);
}
