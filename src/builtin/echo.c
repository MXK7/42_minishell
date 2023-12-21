/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpoussie <mpoussie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 01:39:31 by mpoussie          #+#    #+#             */
/*   Updated: 2023/12/21 09:38:08 by mpoussie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	_builtin_echo(t_settings *settings, t_global *global)
{
	(void)settings;
	int i;
	bool param;

	i = 3;
	param = false;
	while (global->input[i])
	{
		if (global->input[i] == '-' && global->input[i + 1] == 'n')
			param = true;
		else
			ft_printf("%s\n", global->input);
		i++;
	}
	if (!param)
		ft_printf("\n");
	return ;
}
