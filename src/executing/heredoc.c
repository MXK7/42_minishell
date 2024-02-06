/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arazzok <arazzok@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 13:48:44 by arazzok           #+#    #+#             */
/*   Updated: 2024/02/06 18:57:59 by arazzok          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	create_heredoc(t_global *global, char *filename)
{
	int		fd;
	char	*line;
	char	*expanded_line;

	fd = open(filename, O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (fd < 0)
		return (1);
	line = readline("> ");
	while (line && ft_strcmp(line, global->command_list->redirections->str))
	{
		expanded_line = expand_env_var(line);
		write(fd, expanded_line, ft_strlen(expanded_line));
		write(fd, "\n", 1);
		free(expanded_line);
		free(line);
		line = readline("> ");
	}
	free(line);
	close(fd);
	return (0);
}

char	*generate_hd_filename(void)
{
	static int	i = 0;
	char		*number;
	char		*filename;

	number = ft_itoa(i++);
	filename = ft_strjoin("/tmp/.heredoc_file_", number);
	free(number);
	return (filename);
}

int	pre_heredoc(t_global *global, char *filename)
{
	int	exit_code;

	exit_code = 0;
	exit_code = create_heredoc(global, filename);
	global->is_heredoc = true;
	return (exit_code);
}

int	handle_heredoc(t_global *global)
{
	t_command	*command;
	t_lexer		*current;
	int			exit_code;

	exit_code = 0;
	command = global->command_list;
	current = command->redirections;
	while (current)
	{
		if (current->token == DOUBLE_LEFT)
		{
			if (command->heredoc_file_name)
				free(command->heredoc_file_name);
			command->heredoc_file_name = generate_hd_filename();
			exit_code = pre_heredoc(global, command->heredoc_file_name);
			if (exit_code)
			{
				g_exit_status = 1;
				return (reset_global(global));
			}
		}
		current = current->next;
	}
	return (0);
}
