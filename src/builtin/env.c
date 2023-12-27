/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpoussie <mpoussie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 16:11:57 by mpoussie          #+#    #+#             */
/*   Updated: 2023/12/27 08:40:26 by mpoussie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	update_var(t_global *global, const char *env_name,
				const char *new_env);

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
	global->pwd = getcwd(NULL, 0);
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
