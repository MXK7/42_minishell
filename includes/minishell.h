/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpoussie <mpoussie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 13:49:21 by arazzok           #+#    #+#             */
/*   Updated: 2024/01/25 19:10:53 by mpoussie         ###   ########.fr       */
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
# define ERROR_PATH_EGAL "Error: '=' not found in path string\n"

extern bool				exit_requested;

typedef enum s_token
{
	WORD = 1,
	PIPE,
	RIGHT,
	DOUBLE_RIGHT,
	LEFT,
	DOUBLE_LEFT
}						t_token;

typedef struct s_lexer
{
	char				*str;
	t_token				token;
	int					index;
	struct s_lexer		*prev;
	struct s_lexer		*next;
}						t_lexer;

typedef struct s_parser
{
	t_lexer				*lexer_list;
	t_lexer				*redirections;
	int					nb_redirections;
	struct s_global		*global;
}						t_parser;

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
	int					nb_pipes;
	int					*pid;
}						t_global;

typedef struct s_command
{
	char				**str;
	int					(*builtin)(t_global *global);
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

/* ###@ LEXING */
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
							char quote, t_global *global);

void					handle_word(char *input, int *i, t_lexer **current);
void					handle_head(t_lexer **head, t_lexer *current);

/* ###@ PARSING */
t_parser				init_parser(t_global *global);
void					count_pipes(t_global *global);
int						count_args(t_lexer *lexer_list);

t_command				*init_command(char **str, int nb_redirections,
							t_lexer *redirections);
void					push_command(t_command **list, t_command *new);
void					free_command(t_command **list);

int						add_redirection(t_lexer *temp, t_parser *parser);
void					del_redirections(t_parser *parser);

t_lexer					*tokenize(char *input, t_global *global);
t_command				*pre_init_command(t_parser *parser);
int						parser(t_global *global);

/* ###@ EXECUTOR */
void					get_path_exe(t_global *global);
bool					exe_commands(t_global *global);

void					init_execute(t_global *global, char **envp);
int						execute(t_global *global);

void					single_command(t_global *global);

/* ###@ BUILTIN */
char					*get_path(t_global *global);
void					single_command(t_global *global);
void					init_env(t_global *global, char **envp);
char					*get_env(char *env_name, t_global *global);
void					_env_update(t_global *global, const char *env_name,
							const char *new_env);
int						_env_len(char **env);

void					_others(t_global *global);

int (*get_builtin(char *str))(t_global *global);

int						_builtin_exit(t_global *global);
int						_builtin_pwd(t_global *global);
int						_builtin_env(t_global *global);
int						_builtin_echo(t_global *global);
void					_builtin_others(t_global *global);
int						_builtin_cd(t_global *global);
int						_builtin_export(t_global *global);
int						_builtin_unset(t_global *global);

/* ###@ SIGNAL */
void	_signal_newline(int signal __attribute__((unused)));
void	_signal_exit(int signal __attribute__((unused)), t_global *global);

/* ###@ UTILS */
int						count_path(char *path);
int						are_quotes_closed(char *line);
void					free_array(char **array);
void					free_global(t_global *global);

void					init_global(t_global *global);
void					reset_global(t_global *global);
void					free_global(t_global *global);

/* ###@ ERROR */
void					parser_error(int err_code, t_global *global,
							t_lexer *lexer_list);
int						double_token_error(t_global *global,
							t_lexer *lexer_list, t_token token);
int						handle_error(int err_code, t_global *global);

#endif
