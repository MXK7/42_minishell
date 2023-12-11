/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpoussie <mpoussie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 14:21:38 by mpoussie          #+#    #+#             */
/*   Updated: 2023/12/08 21:38:17 by mpoussie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	prompt(t_settings *settings, t_global *global, char **envp)
{
	signal(SIGINT, handler_signal);
	// signal(SIGQUIT, _signal_exit);
	builtin_start(global, envp);
	// printf("COUNT PATH : %d\n", count_path(global->path));
	
	while (settings->exitRequested)
	{
		global->input = readline("\033[1;37m-\033[0m \033[1;31m\033[1;1mAMS\033[0m \033[1;33m\033[1;93m✗\033[0m ");
		handler_builtin(settings, global);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_global	*global;
	t_settings	*settings;

	(void)argv;
	global = (t_global *)malloc(sizeof(global));
	settings = (t_settings *)malloc(sizeof(settings));
	if (argc == 1 && (settings != NULL && global != NULL))
	{
		settings->exitRequested = true;
		prompt(settings, global, envp);
		free(global->input);
	}
	free(global);
	free(settings);
	return (0);
}
