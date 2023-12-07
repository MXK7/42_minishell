/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpoussie <mpoussie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 14:17:15 by mpoussie          #+#    #+#             */
/*   Updated: 2023/12/07 18:35:51 by mpoussie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include <dirent.h>
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
	bool	exitRequested;
}			t_settings;

typedef struct s_global
{
	char	*input;
	char	**env;
	char	*pwd;
}			t_global;

/// @param settings
/// @param global
/// @param envp
/// @param unused_signal
void		handler_signal(int signal __attribute__((unused)));
void		_signal_exit(int signal __attribute__((unused)));

void		handler_parse_cmd(t_settings *settings, t_global *global);

void		handler_builtin(t_settings *settings, t_global *global);
void		builtin_start(t_global *global, char **envp);
bool		builtin_exist(t_global *global);

void		_env(t_global *global, char **envp);
void		_builtin_env(t_global *global);
void		_builtin_pwd(t_global *global);
void		_builtin_others(void);
void		_builtin_echo(void);

int			count_path(char *path);

#endif