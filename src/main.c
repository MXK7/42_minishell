/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpoussie <mpoussie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 14:21:38 by mpoussie          #+#    #+#             */
/*   Updated: 2024/01/24 23:40:51 by mpoussie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	init_sh(t_global *global);
static int  pre_execute(t_global *global);

bool		exit_requested = true;

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
	init_sh(global);
	free_global(global);
	return (0);
}

static int	init_sh(t_global *global)
{
	char	*temp;

	temp = NULL;
	while (exit_requested)
	{
		global->input = readline("AMS $ ");
		temp = ft_strtrim(global->input, " ");
		free(global->input);
		global->input = temp;
		if (!global->input)
		{
			ft_putendl_fd("\n", STDOUT_FILENO);
			free(global->input);
			return (0);
		}
		if (global->input[0] == '\0')
		{
			free(global->input);
			continue ;
		}
		add_history(global->input);
		if (!are_quotes_closed(global->input))
			return (free(global->input), handle_error(2, global));
		global->lexer_list = tokenize(global->input);
		free(global->input);
		parser(global);
        pre_execute(global);
        reset_global(global);
	}
	return (1);
}

static int pre_execute(t_global *global)
{
    if (global->nb_pipes == 0)
		single_command(global);
    else
    {
		// TODO :
        // global->pid = ft_calloc(sizeof(int), global->nb_pipes + 2);
        // if (!global->pid)
		// 	return (handle_error(1, global));
        // execute(global);
    }
    return (0);
}
