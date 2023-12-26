/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpoussie <mpoussie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 10:15:48 by mpoussie          #+#    #+#             */
/*   Updated: 2023/12/26 13:15:26 by mpoussie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	_builtin_exit(t_settings *settings, t_global *global)
{
	free_alloc(global, settings);
	settings->exit_requested = false;
	exit(0);
}
