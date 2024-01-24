/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpoussie <mpoussie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 14:51:03 by arazzok           #+#    #+#             */
/*   Updated: 2024/01/24 02:39:04 by mpoussie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_execute(t_global *global, char **envp)
{
	global->env = NULL;
	global->args_path = NULL;
	init_env(global, envp);
	global->path = get_env("PATH=", global);
	global->pwd = getcwd(NULL, 0);
	global->nbr_path = count_path(global->path);
	get_path_exe(global);
}
