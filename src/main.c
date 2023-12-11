/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arazzok <arazzok@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 14:21:38 by mpoussie          #+#    #+#             */
/*   Updated: 2023/12/11 17:58:48 by arazzok          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_line(t_global *global)
{
	char	*line;

	line = readline("\x1b[31;1m" "AMS " "\x1b[m");
	if (line)
	{
		if (line[0] == '\0')
		{
			free(line);
			return (0);
		}
		add_history(line);
		rl_redisplay();
		global->input = ft_strdup(line);
		free(line);
		return (1);
	}
	else
		exit (1);
}

static void	prompt(t_settings *settings, t_global *global, char **envp)
{
	builtin_start(global, envp);
	
	while (settings->exitRequested)
	{
		// signal(SIGINT, handler_signal);
		// signal(SIGQUIT, _signal_exit);
		if (!handle_line(global))
			continue ;
		lexer(global);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_global	*global;
	t_settings	*settings;

	(void)argv;
	global = (t_global *)malloc(sizeof(t_global));
	settings = (t_settings *)malloc(sizeof(t_settings));
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
