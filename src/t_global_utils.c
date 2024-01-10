/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_global_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arazzok <arazzok@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 15:27:54 by arazzok           #+#    #+#             */
/*   Updated: 2024/01/10 15:40:31 by arazzok          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_global(t_global *global)
{
	global->nbr_path = 0;
	global->input = NULL;
	global->pwd = NULL;
	global->path = NULL;
	global->token = NULL;
	global->lexer_list = NULL;
	global->command_list = NULL;
}

// TODO: Refaire la fonction pour qu'elle free correctement toute la struct global
// ? Renommer free_global ?
void	free_minishell(t_global *global)
{
	int	i;

	i = 0;
	while (global->env[i])
	{
		free(global->env[i]);
		i++;
	}
	i = 0;
	while (global->args_path[i])
	{
		free(global->args_path[i]);
		i++;
	}
	free(global->path);
	free(global->token);
	free(global);
}
