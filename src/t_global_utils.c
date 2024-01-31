/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_global_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpoussie <mpoussie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 15:27:54 by arazzok           #+#    #+#             */
/*   Updated: 2024/01/31 18:47:45 by mpoussie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_global(t_global *global)
{
	global->input = NULL;
	global->token = NULL;
	global->lexer_list = NULL;
	global->command_list = NULL;
	global->nb_pipes = 0;
	global->pid = NULL;
}

int	reset_global(t_global *global)
{
	free_command(&global->command_list);
	free(global->input);
	if (global->pid)
		free(global->pid);
	init_global(global);
	init_sh(global);
	return (1);
}

void	free_global(t_global *global)
{
	free_array(global->argv);
	free_array(global->args_path);
	free_array(global->env);
	free(global->pwd);
	free(global->token);
	free_lexer(&global->lexer_list);
	free_command(&global->command_list);
	if (global->pid)
		free(global->pid);
	free(global->path);
	free(global);
}
