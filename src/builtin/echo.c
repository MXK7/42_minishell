/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpoussie <mpoussie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 01:39:31 by mpoussie          #+#    #+#             */
/*   Updated: 2024/01/25 17:12:17 by mpoussie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// TODO handler echo flag

int	_builtin_echo(t_global *global)
{
	int i = 1;
	bool new_line = false;

	while (global->command_list->str[i] != NULL
		&& global->command_list->str[i][0] == '-'
		&& ft_strchr(global->command_list->str[i], 'n'))
	{
		new_line = true;
		i++;
	}
	while (global->command_list->str[i] != NULL)
	{
		ft_putstr_fd(global->command_list->str[i], STDOUT_FILENO);
		if (global->command_list->str[i + 1] != NULL)
			ft_putstr_fd(" ", STDOUT_FILENO);
		i++;
	}
	if (!new_line)
		ft_printf("\n");
	return (0);
}