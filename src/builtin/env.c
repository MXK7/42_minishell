/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpoussie <mpoussie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 16:11:57 by mpoussie          #+#    #+#             */
/*   Updated: 2023/12/22 18:34:56 by mpoussie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	_env(t_global *global, char **envp)
{
	int	i;
	int	j;

	i = 0;
	while (envp[i])
		i++;
	global->env = malloc(sizeof(char **) * (i + 1));
	if (global->env == NULL)
		return ;
	j = 0;
	while (j < i)
	{
		global->env[j] = ft_strdup(envp[j]);
		j++;
	}
	global->env[j] = NULL;
	i = 0;
	while (global->env[i])
	{
		if (global->env[i][0] == 'P' && global->env[i][1] == 'A'
			&& global->env[i][2] == 'T' && global->env[i][3] == 'H')
			global->path = global->env[i];
		i++;
	}
}
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

void	_update_env(t_global *global, char *env_name, char *new_env)
{
	int	i;

	i = 0;
	while (global->env[i])
	{
		if (ft_strcmp(global->env[i], env_name) == 0)
		{
			free(global->env[i]);
			new_env = ft_strjoin("PWD=", new_env);
			global->env[i] = ft_strdup(new_env);
		}
		i++;
	}
}

void	_builtin_env(t_global *global)
{
	int	i;

	i = 0;
	while (global->env[i] != NULL)
	{
		ft_putstr_fd(global->env[i], STDOUT_FILENO);
		ft_putstr_fd("\n", STDOUT_FILENO);
		i++;
	}
}
