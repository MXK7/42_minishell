/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arazzok <arazzok@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 10:15:48 by mpoussie          #+#    #+#             */
/*   Updated: 2024/01/26 14:09:43 by arazzok          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_str_digit(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

int	_builtin_exit(t_global *global)
{
	int	exit_code;

	if (global->command_list->str[1] && global->command_list->str[2])
		return (ft_putstr_fd("exit\nams: exit: too many arguments\n",
				STDERR_FILENO), 1);
	if (!global->command_list->str[1])
		exit_code = 0;
	else if (global->command_list->str[1]
		&& is_str_digit(global->command_list->str[1]))
		exit_code = ft_atoi(global->command_list->str[1]);
	else
	{
		ft_putstr_fd("exit\nams: exit: ", STDERR_FILENO);
		ft_putstr_fd(global->command_list->str[1], STDERR_FILENO);
		ft_putstr_fd(": numeric argument required\n", STDERR_FILENO);
		exit_code = 2;
	}
	free_global(global);
	exit(exit_code);
}
