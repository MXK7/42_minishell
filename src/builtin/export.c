/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpoussie <mpoussie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/26 07:38:31 by mpoussie          #+#    #+#             */
/*   Updated: 2024/02/06 21:45:05 by mpoussie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	_builtin_export(t_global *global)
{
	int	i;

	i = 0;
	while (global->command_list->str[i])
		i++;
	if (i == 2)
	{
		if (is_exist_env(ft_strtoupper(global->command_list->str[1]), global))
			update_env(global, ft_strtoupper(global->command_list->str[1]),
				global->command_list->str[2]);
		else
			add_env(global, global->command_list->str[1]);
		return (0);
	}
	else if (i == 1)
	{
		i = 0;
		while (global->env[i])
		{
			if (global->env[i][0] != '\0')
				ft_printf("declare -x %s\n", global->env[i]);
			i++;
		}
	}
	return (0);
}
