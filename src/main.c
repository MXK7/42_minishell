/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arazzok <arazzok@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 14:21:38 by mpoussie          #+#    #+#             */
/*   Updated: 2023/12/29 12:59:34 by arazzok          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	init_sh(t_settings *settings, t_global *global, char **envp);

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
	free(global);
	free(settings);
	return (0);
}

static void	init_sh(t_settings *settings, t_global *global, char **envp)
{
	signal(SIGINT, handler_signal);
	builtin_start(global, envp);
	while (settings->exit_requested)
	{
		global->input = readline("AMS $ ");
		parser(global);
		// handler_builtin(settings, global);
		add_history(global->input);
		free(global->input);
	}
}
