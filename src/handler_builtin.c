/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler_builtin.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpoussie <mpoussie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 21:44:54 by mpoussie          #+#    #+#             */
/*   Updated: 2023/12/06 16:57:18 by mpoussie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handler_builtin(t_settings *settings, t_global *global)
{
	if (ft_strcmp(global->input, "exit") == 0)
		settings->exitRequested = false;
	else if (ft_strcmp(global->input, "pwd") == 0)
		printf("%s\n", getcwd(NULL, 0));
	if (ft_strcmp(global->input, "env") == 0)
		print_env(global);
}
