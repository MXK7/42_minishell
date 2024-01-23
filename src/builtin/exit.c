/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpoussie <mpoussie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 10:15:48 by mpoussie          #+#    #+#             */
/*   Updated: 2024/01/23 16:32:39 by mpoussie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// TODO: tu vas me refaire ca au propre fdp
int	_builtin_exit(t_global *global)
{
	(void)global;
	exit_requested = false;
	exit(-1);
}
