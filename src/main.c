/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arazzok <arazzok@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 14:21:38 by mpoussie          #+#    #+#             */
/*   Updated: 2024/01/10 19:24:09 by arazzok          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	init_sh(t_global *global);

bool		exit_requested = true;

int	main(int argc, char **argv, char **envp)
{
	t_global	*global;

	(void)argv;
	(void)envp;
	if (argc != 1)
		return (ft_printf("Error.\nNo argument accepted.\n"), 1);
	global = malloc(sizeof(t_global));
	if (!global)
		return (ft_printf("Error.\nMalloc error.\n"), 1);
	init_global(global);
	// builtin_start(global, envp);
	init_sh(global);
	return (0);
}

static int	init_sh(t_global *global)
{
	char	*temp;

	while (exit_requested)
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
			return (handle_error(1, global));
		parser(global);
		// Execute
	}
    return (1);
}
