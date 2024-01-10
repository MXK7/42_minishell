/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arazzok <arazzok@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 14:17:15 by mpoussie          #+#    #+#             */
/*   Updated: 2024/01/10 18:54:45 by arazzok          ###   ########.fr       */
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
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <time.h>
# include <unistd.h>

# define MAX_TOKENS 100
# define CTRL_D '\004'
# define ERROR_PATH_EGAL "Error: '=' not found in path\n string"

extern bool				exit_requested;

typedef enum s_token
{
	WORD = 1,
	PIPE,
	LEFT,
	DOUBLE_LEFT,
	RIGHT,
	DOUBLE_RIGHT
}						t_token;

typedef struct s_lexer
{
	char				*str;
	t_token				token;
	int					index;
	struct s_lexer		*prev;
	struct s_lexer		*next;
}						t_lexer;

typedef struct s_global
{
	char				**argv;
	char				**args_path;
	char				**env;
	int					nbr_path;
	char				*input;
	char				*pwd;
	char				*path;
	char				*token;
	t_lexer				*lexer_list;
	struct s_command	*command_list;
}						t_global;

typedef struct s_command
{
	char				**str;
	void				(*builtin)(t_global *global);
	int					nb_redirections;
	char				*heredoc_file_name;
	t_lexer				*redirections;
	struct s_command	*prev;
	struct s_command	*next;
}						t_command;

/// @param settings Structure secondaire pour la gestion du projet
/// @param global Structure principale pour les datas
/// @param envp Variables d'environement
/// @param unused_signal

/* ###@ PARSING */
t_lexer					*init_lexer(char *str, t_token token);
void					clear_one(t_lexer **list);
void					del_first(t_lexer **list);
void					del_one(t_lexer **list, int index);
void					free_lexer(t_lexer **list);

int						is_whitespace(char c);
int						is_operator(char c);
int						is_quote(char c);
void					skip_whitespaces(char *input, int *i);
int						get_word_len(char *input, int i);

void					handle_operator(char *input, int *i, t_lexer **current,
							char operator);
void					handle_quote(char *input, int *i, t_lexer **current,
							char quote);
void					handle_word(char *input, int *i, t_lexer **current);
void					handle_head(t_lexer **head, t_lexer *current);

void					handle_token(t_lexer *lexer, t_command *command);
void					handle_cmd_head(t_command **head, t_command *current);

int						is_redirection(t_token token);
int						get_str_size(char **str);

t_command				*init_command(void);
t_lexer					*tokenize(char *input);
t_command				*tokens_to_commands(t_lexer *lexer);
void					parser(t_global *global);

/* ###@ EXECUTOR */
void					handler_exe(t_global *global);
bool					exe_commands(t_global *global);

/* ###@ BUILTIN */
void					handler_builtin(t_global *global);
void					builtin_start(t_global *global, char **envp);

void					_env(t_global *global, char **envp);
char					*_env_get(char *env_name, t_global *global);
void					_env_update(t_global *global, const char *env_name,
							const char *new_env);
int						_env_len(char **env);

void					_others(t_global *global);

void					_builtin_exit(t_global *global);
void					_builtin_pwd(t_global *global);
void					_builtin_env(t_global *global);
void					_builtin_echo(t_global *global);
void					_builtin_others(t_global *global);
int						_builtin_cd(t_global *global);
void					_builtin_export(t_global *global);
void					_builtin_unset(t_global *global);

/* ###@ SIGNAL */
void					_signal_newline(int signal __attribute__((unused)));
void					_signal_exit(int signal __attribute__((unused)),
							t_global *global);

/* ###@ UTILS */
int						count_path(char *path);
int						are_quotes_closed(char *line);

void					init_global(t_global *global);
void					free_minishell(t_global *global);

/* ###@ UTILS */
int						handle_error(int err_code, t_global *global);

#endif
