/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arazzok <arazzok@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 14:21:38 by mpoussie          #+#    #+#             */
/*   Updated: 2024/01/03 11:44:09 by arazzok          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	init_sh(t_global *global, char **envp);

bool		exit_requested = true;

int	main(int argc, char **argv, char **envp)
{
	t_global	*global;

	(void)argv;
	global = malloc(sizeof(t_global));
	if (argc == 1 && global != NULL)
		init_sh(global, envp);
	// free(global);
	free_minishell(global);
	return (0);
}

static void	init_sh(t_global *global, char **envp)
{
	signal(SIGINT, _signal_newline);
	signal(SIGQUIT, SIG_IGN);
	builtin_start(global, envp);
	while (exit_requested)
	{
		global->input = readline("AMS $ ");
		parser(global);
		// handler_builtin(global);
		add_history(global->input);
		free(global->input);
		_signal_exit(0);
	}
}
