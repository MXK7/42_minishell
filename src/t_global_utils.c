/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_global_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arazzok <arazzok@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 15:27:54 by arazzok           #+#    #+#             */
/*   Updated: 2024/01/19 15:39:19 by arazzok          ###   ########.fr       */
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
    global->nb_pipes = 0;
}

void     reset_global(t_global *global)
{
    free_command(&global->command_list);
    // free(global->args);
    if (global->pid)
        free(global->pid);
    // free_array(global->path);
    init_global(global);
    // global->reset = true;
}

// TODO: Refaire la fonction pour qu'elle free correctement toute la struct global
void	free_global(t_global *global)
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
