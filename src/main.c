/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpoussie <mpoussie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 14:21:38 by mpoussie          #+#    #+#             */
/*   Updated: 2023/12/15 08:52:31 by mpoussie         ###   ########.fr       */
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
		handler_builtin(settings, global);
		add_history(global->input);
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
		settings->exit_requested = true;
		init_sh(settings, global, envp);
		free(global->input);
	}
	free(global->input);
	free(global);
	free(settings);
	return (0);
}
