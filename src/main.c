/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arazzok <arazzok@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 14:21:38 by mpoussie          #+#    #+#             */
/*   Updated: 2023/12/22 11:35:00 by arazzok          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	init_sh(t_settings *settings, t_global *global, char **envp)
{
	signal(SIGINT, handler_signal);
	builtin_start(global, envp);
	while (settings->exit_requested)
	{
		global->input = readline("AMS $ ");
		add_history(global->input);
		parser(global);
		handler_builtin(settings, global);
		// if (!global->input)
		// {
		// 	_builtin_exit(settings, global);
		// }
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_global	*global;
	t_settings	*settings;

	(void)argv;
	global = malloc(sizeof(t_global));
	settings = malloc(sizeof(t_settings));
	settings->exit_requested = true;
	if (argc == 1 && (settings != NULL && global != NULL))
		init_sh(settings, global, envp);
	free(global->input);
	free(global);
	free(settings);
	return (0);
}
