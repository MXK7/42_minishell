/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpoussie <mpoussie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 14:21:38 by mpoussie          #+#    #+#             */
/*   Updated: 2023/12/05 23:27:10 by mpoussie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	prompt(t_settings *settings, t_global *global, char **envp)
{
	signal(SIGINT, handler_signal);
	signal(SIGQUIT, _signal_exit);
	handler_parse_cmd(settings, global);
	(void)envp; // TODO: ENVP "env"
	while (settings->exitRequested)
	{
		global->input = readline("Minishell > ");
		free(global->input);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_global	*global;
	t_settings	*settings;

	(void)argv;
	global = (t_global *)malloc(sizeof(global));
	settings = (t_settings *)malloc(sizeof(settings));
	if (argc == 1 || (settings != NULL && global == NULL))
	{
		settings->exitRequested = true;
		prompt(settings, global, envp);
		free(global);
		free(settings);
	}
	return (0);
}
