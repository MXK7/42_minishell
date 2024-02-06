/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpoussie <mpoussie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 13:49:21 by arazzok           #+#    #+#             */
/*   Updated: 2024/02/06 21:21:08 by mpoussie         ###   ########.fr       */
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

# define ERROR_PATH_EGAL "Error: '=' not found in path string\n"
# define ERROR_CD_ARGS "ams: cd: too many arguments.\n"
# define ERROR_UNSET_ARGS "unset: not enough arguments\n"
# define ERROR_ENV_VAR "Error code: 1, var en_len"
# define ERROR_MAIN_ARGS "No argument accepted.\n"
# define ERROR_MALLOC "Global malloc error.\n"

typedef enum e_token
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
	char				*old_pwd;
	bool				is_heredoc;
	bool				is_reset;
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

extern int				g_exit_status;

/* ###@ MAIN */
int						init_sh(t_global *global);

/* ###@ LEXING */
t_lexer					*init_lexer(char *str, t_token token);
void					clear_one(t_lexer **list);
void					del_first(t_lexer **list);
void					del_one(t_lexer **list, int index);
void					free_lexer(t_lexer **list);
int						is_whitespace(char c);
int						is_operator(char c);
void					skip_whitespaces(char *input, int *i);
int						get_word_len(char *input, int i);
char					*ft_strndup(const char *src, size_t size);

void					handle_single_quote(char *input, int *i,
							t_lexer **current, char quote);
void					handle_double_quotes(char *input, int *i,
							t_lexer **current, char quote);
void					handle_operator(char *input, int *i, t_lexer **current,
							char operator);
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
t_command				*command_first(t_command *list);
int						add_redirection(t_lexer *temp, t_parser *parser);
void					del_redirections(t_parser *parser);

t_lexer					*tokenize(char *input);
t_command				*pre_init_command(t_parser *parser);
int						parser(t_global *global);

/* ###@ EXPANDING */
char					*expand_env_var(char *command);
char					*ft_strncpy(char *dest, char *src, size_t len);
void					call_expander(t_global *global);

/* ###@ EXECUTOR */
void					get_path_exe(t_global *global);
bool					exe_commands(t_global *global);
int						execute(t_global *global);
int						handle_redirection(t_command *command);
int						handle_heredoc(t_global *global);
void					handle_command(t_global *global);

/* ###@ BUILTIN */
void					single_command(t_global *global);
char					*get_path(t_global *global);
void					init_env(t_global *global, char **envp);
char					*get_env(char *env_name, t_global *global);
void					update_env(t_global *global, const char *env_name,
							const char *new_env);
void					add_env(t_global *global, char *new_var);
bool					is_exist_env(char *env_name, t_global *global);
size_t					tab_len(char **tab);
void					_others(t_global *global);

int						_builtin_exit(t_global *global);
int						_builtin_pwd(t_global *global);
int						_builtin_env(t_global *global);
int						_builtin_echo(t_global *global);
int						_builtin_cd(t_global *global);
int						_builtin_export(t_global *global);
int						_builtin_unset(t_global *global);

/* ###@ SIGNAL */
void					handle_sigint(int signal);
void					handle_sigint_cmd(int signal);
void					handle_sigint_heredoc(int signal);
void					handle_sigquit(int signal);
void					init_signals(void);

/* ###@ UTILS */
int						count_path(char *path);
int						are_quotes_closed(char *line);
void					free_array(char **array);
void					init_global(t_global *global);
void					init_execute(t_global *global, char **envp);
int						reset_global(t_global *global);
void					free_global(t_global *global);

/* ###@ ERROR */
void					parser_error(int err_code, t_global *global,
							t_lexer *lexer_list);
int						double_token_error(t_global *global,
							t_lexer *lexer_list, t_token token);
int						handle_error(int err_code, t_global *global);

#endif
