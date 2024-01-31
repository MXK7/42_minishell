/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_handler.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arazzok <arazzok@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 15:49:31 by arazzok           #+#    #+#             */
/*   Updated: 2024/01/30 21:00:04 by arazzok          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	redirections_input(t_global *global, t_lexer *redirections)
{
	(void)global;
	(void)redirections;
	printf("Redirections input\n");
}

void	redirections_heredoc(t_global *global, t_lexer *redirections)
{
	(void)global;
	(void)redirections;
	printf("Redirections heredoc\n");
}

int	redirections_output(t_lexer *redirections)
{
	char	*filename;
	int		fd;

    if (!redirections)
        return (1);
	filename = redirections->str;
	fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
	{
		ft_putstr_fd("ams: outfile: open error\n", STDERR_FILENO);
		return (1);
	}
	if (dup2(fd, STDOUT_FILENO) < 0)
    {
        ft_putstr_fd("ams: outfile: dup2 error\n", STDERR_FILENO);
        return (1);
    }
	close(fd);
	return (0);
}

void	redirections_append(t_global *global, t_lexer *redirections)
{
	(void)global;
	(void)redirections;
	printf("Redirections append\n");
}

void	redirections_handler(t_lexer *redirections)
{
	t_lexer    *start;

	start = redirections;
    while (redirections)
    {
        if (redirections->token == LEFT)
            redirections_input(global, redirections);
        else if (redirections->token == DOUBLE_LEFT)
            redirections_heredoc(global, redirections);
        else if (redirections->token == RIGHT)
            redirections_output(redirections);
        else if (redirections->token == DOUBLE_RIGHT)
            redirections_append(global, redirections);
        redirections = redirections->next;
    }
    redirections = start;
}
