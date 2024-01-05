/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arazzok <arazzok@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 14:21:38 by mpoussie          #+#    #+#             */
/*   Updated: 2024/01/05 19:03:51 by arazzok          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	init_sh(t_global *global, char **envp);

bool		exit_requested = true;

int	main(int argc, char **argv, char **envp)
{
	t_global	*global;

	(void)argv;
	if (argc != 1)
		return (ft_printf("Error.\nNo argument accepted.\n"), 1);
	global = malloc(sizeof(t_global));
	if (!global)
		return (ft_printf("Error.\nMalloc error.\n"), 1);
	init_sh(global, envp);
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
		_signal_exit(0, global);
	}
}
