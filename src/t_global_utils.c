/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_global_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arazzok <arazzok@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 15:27:54 by arazzok           #+#    #+#             */
/*   Updated: 2024/02/07 16:02:08 by arazzok          ###   ########.fr       */
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
	global->is_heredoc = false;
	global->is_reset = false;
	init_signals();
}

void	init_execute(t_global *global, char **envp)
{
	global->env = NULL;
	global->args_path = NULL;
	init_env(global, envp);
	global->path = NULL;
	global->pwd = getcwd(NULL, 1024);
	global->old_pwd = global->pwd;
	global->nbr_path = 0;
}

int	reset_global(t_global *global)
{
	free_command(&global->command_list);
	free(global->input);
	if (global->pid)
		free(global->pid);
	init_global(global);
	global->is_reset = true;
	init_sh(global);
	return (1);
}

void	free_global(t_global *global)
{
	free(global->input);
	if (global->args_path)
		free_array(global->args_path);
	free_array(global->env);
	free(global->pwd);
	free(global->token);
	free_lexer(&global->lexer_list);
	free_command(&global->command_list);
	if (global->pid)
		free(global->pid);
	if (global->path)
		free(global->path);
	free(global);
}
