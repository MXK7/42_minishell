/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpoussie <mpoussie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 14:17:15 by mpoussie          #+#    #+#             */
/*   Updated: 2023/12/05 21:52:06 by mpoussie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H


# include "libft.h"
# include <readline/history.h>
# include <readline/readline.h>
# include <setjmp.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <time.h>
# include <unistd.h>

# define MAX_TOKENS 100
# define CTRL_D '\004'

typedef struct s_settings
{
	bool exitRequested;
}			t_settings;

typedef struct s_global
{
	char	*input;
	char	**env;
}			t_global;

/// @param settings
/// @param global
/// @param envp
void		handler_signal(int signal __attribute__((unused)));
void		_signal_exit(int signal __attribute__((unused)));
void		handler_parse_cmd(t_settings *settings, t_global *global);
void		handler_builtin(t_settings *settings, t_global *global);
void		get_env(t_global *global, char **envp);
int			print_env(t_global *global);

#endif