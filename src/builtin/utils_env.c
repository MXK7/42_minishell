/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpoussie <mpoussie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 21:19:59 by mpoussie          #+#    #+#             */
/*   Updated: 2024/02/07 03:18:14 by mpoussie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	add_env_res(t_global *global, int i, char **result);

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

char	*get_env(char *env_name, t_global *global)
{
	char	*res;
	char	*equal_sign;
	size_t	en_len;
	size_t	index_env;

	res = NULL;
	en_len = ft_strlen(env_name);
	if (en_len == 0)
	{
		ft_printf(ERROR_ENV_VAR);
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

void	add_env(t_global *global, char *new_var)
{
	char	**result;
	size_t	i;
	size_t	x;

	x = 0;
	i = 0;
	while (global->env[i] != NULL)
		i++;
	result = (char **)malloc(sizeof(char *) * (i + 2));
	if (!result)
		return ;
	while (x < i)
	{
		result[x] = ft_strdup(global->env[x]);
		if (!result[x])
		{
			free_array(result);
			return ;
		}
		x++;
	}
	result[i] = ft_strdup(new_var);
	result[i + 1] = NULL;
	add_env_res(global, i, result);
}

static void	add_env_res(t_global *global, int i, char **result)
{
	if (!result[i])
	{
		free_array(result);
		return ;
	}
	free_array(global->env);
	global->env = result;
}

void	edit_env(t_global *global, char *var_env, char *var_v)
{
	char	*tmp;

	tmp = NULL;
	if (var_v)
		var_env = ft_strjoin(var_env, "=");
	if (!var_env)
		return ;
	if (is_exist_env(var_env, global))
	{
		update_env(global, var_env, var_v);
		if (var_v)
			free(var_env);
	}
	else
	{
		if (var_v)
		{
			tmp = ft_strjoin(var_env, var_v);
			free(var_env);
			if (!tmp)
				return ;
			add_env(global, tmp);
			free(tmp);
		}
		else
			add_env(global, var_env);
	}
}
