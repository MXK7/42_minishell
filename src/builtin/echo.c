/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpoussie <mpoussie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 01:39:31 by mpoussie          #+#    #+#             */
/*   Updated: 2024/01/25 00:05:30 by mpoussie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// TODO handler echo flag

int	_builtin_echo(t_global *global)
{
	int		i;
	bool	param;

	i = 1;
	param = false;
	while (global->command_list->str[i] != NULL && !ft_strcmp(global->command_list->str[i], "-n"))
	{
		param = true;
		i++;
	}
	while (i >= 1)
	{
		ft_putstr_fd(global->command_list->str[i], STDOUT_FILENO);
		if (0 < (i - 1))
			ft_putstr_fd(" ", STDOUT_FILENO);
		i--;
	}
	if (param)
		ft_printf("\n");
	return (0);
}
