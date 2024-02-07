/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpoussie <mpoussie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/27 08:36:51 by mpoussie          #+#    #+#             */
/*   Updated: 2024/02/07 05:52:39 by mpoussie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	_builtin_unset(t_global *global)
{
	int	i;

	if (global->command_list->str[1] == NULL)
	{
		ft_printf(ERROR_UNSET_ARGS);
		return (1);
	}
	i = 1;
	while (global->command_list->str[i] != NULL)
	{
		global->env = remove_env(global->env, global->command_list->str[i]);
		i++;
	}
	return (0);
}
