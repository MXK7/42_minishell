/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arazzok <arazzok@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 14:21:38 by mpoussie          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2024/01/29 16:28:19 by mpoussie         ###   ########.fr       */
=======
/*   Updated: 2024/01/29 23:01:59 by arazzok          ###   ########.fr       */
>>>>>>> a2d3a37a34436663989a34d21664e75aabfe3e96
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	init_sh(t_global *global);
static int	pre_execute(t_global *global);

int	main(int argc, char **argv, char **envp)
{
	t_global	*global;

	(void)argv;
	if (argc != 1)
		return (ft_printf("Error.\nNo argument accepted.\n"), 1);
	global = calloc(1, sizeof(t_global));
	if (!global)
		return (ft_printf("Error.\nGlobal malloc error.\n"), 1);
	init_global(global);
	init_execute(global, envp);
	signal(SIGINT, _signal_newline);
	signal(SIGQUIT, SIG_IGN);
	init_sh(global);
	free_global(global);
	return (0);
}

static int	init_sh(t_global *global)
{
	char	*temp;

	while (1)
	{
		global->input = readline("AMS $ ");
		temp = ft_strtrim(global->input, " ");
		free(global->input);
		global->input = temp;
		if (!global->input)
		{
			ft_putendl_fd("exit", STDOUT_FILENO);
			exit(0);
		}
		if (global->input[0] == '\0')
			continue ;
		add_history(global->input);
		if (!are_quotes_closed(global->input))
			return (handle_error(2, global));
		global->lexer_list = tokenize(global->input);
		free(global->input);
		parser(global);
		pre_execute(global);
		reset_global(global);
	}
	return (1);
}

static int	pre_execute(t_global *global)
{
	if (global->nb_pipes == 0)
		single_command(global);
	else
	{
		global->pid = ft_calloc(sizeof(int), global->nb_pipes + 2);
		if (!global->pid)
			return (handle_error(1, global));
		execute(global);
	}
	return (0);
}
