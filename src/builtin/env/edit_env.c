/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edit_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpoussie <mpoussie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 21:19:59 by mpoussie          #+#    #+#             */
/*   Updated: 2024/02/07 05:57:03 by mpoussie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	edit_env_res(t_global *global, char *var_v, char *var_env,
				char *tmp);

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
		edit_env_res(global, var_v, var_env, tmp);
}

static void	edit_env_res(t_global *global, char *var_v, char *var_env,
		char *tmp)
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
