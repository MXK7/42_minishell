/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpoussie <mpoussie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 14:17:15 by mpoussie          #+#    #+#             */
/*   Updated: 2023/12/15 09:10:34 by mpoussie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include <dirent.h>
# include <errno.h>
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <setjmp.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <time.h>
# include <unistd.h>

# define MAX_TOKENS 100
# define CTRL_D '\004'
# define ERROR_PATH_EGAL "Error: '=' not found in path\n string"

typedef struct s_settings
{
	bool	exit_requested;
}			t_settings;

typedef struct s_global
{
	int		nbr_path;
	char	**args_path;
	char	**env;
	char	*input;
	char	*pwd;
	char	*path;
	char	*token;
	char	**argv;
}			t_global;

/// @param settings
/// @param global
/// @param envp
/// @param unused_signal

/* #@ SIGNAL */
void		handler_signal(int signal __attribute__((unused)));
void		_signal_exit(int signal __attribute__((unused)));

/* #@ PARSING */
void		handler_parse_cmd(t_settings *settings, t_global *global);

/* #@ EXECUTOR */
void		handler_exe(t_global *global);
bool		exe_commands(t_global *global);

/* #@ BUILTIN */
void		handler_builtin(t_settings *settings, t_global *global);
void		builtin_start(t_global *global, char **envp);
bool		builtin_exist(t_global *global);

void		_env(t_global *global, char **envp);
void		_others(t_global *global);

void		_builtin_exit(t_settings *settings);
void		_builtin_pwd(t_global *global);
void		_builtin_env(t_global *global);
void		_builtin_echo(t_settings *settings, t_global *global);
void		_builtin_others(t_global *global);

/* #@ UTILS */
char		**split_string(const char *str, int *numWords);
int			count_path(char *path);

#endif