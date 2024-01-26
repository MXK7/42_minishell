/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_global_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arazzok <arazzok@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 15:27:54 by arazzok           #+#    #+#             */
/*   Updated: 2024/01/26 13:18:43 by arazzok          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_global(t_global *global)
{
	// global->nbr_path = 0;
	global->input = NULL;
	// global->pwd = NULL;
	// global->path = NULL;
	global->token = NULL;
	global->lexer_list = NULL;
	global->command_list = NULL;
    global->nb_pipes = 0;
	global->pid = NULL;
}

void     reset_global(t_global *global)
{
    free_command(&global->command_list);
    if (global->pid)
        free(global->pid);
    init_global(global);
}

void free_global(t_global *global)
{
	free_array(global->argv);
	free_array(global->args_path);
	free_array(global->env);
	free(global->pwd);
	free(global->token);
	free_lexer(&global->lexer_list);
	free_command(&global->command_list);
	free(global->pid);
	free(global);
}
