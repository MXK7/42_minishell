/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arazzok <arazzok@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 14:45:38 by arazzok           #+#    #+#             */
/*   Updated: 2024/01/31 15:27:33 by arazzok          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    handle_outfile(t_lexer *redirections)
{
    char    *pathname;
    int     fd;

    pathname = redirections->str;
    fd = open(pathname, O_CREAT | O_RDWR | O_TRUNC, 0644);
    if (fd < 0)
    {
        ft_putstr_fd("ams: open error\n", STDOUT_FILENO);
        return ;
    }
    if (dup2(fd, STDOUT_FILENO) < 0)
    {
        ft_putstr_fd("ams: dup2 error\n", STDOUT_FILENO);
        return ;
    }
}

void    handle_append()
{

}

void    handle_infile()
{

}

void    handle_heredoc()
{
    
}
void    handle_redirection(t_global *global)
{
    t_lexer *redirections;

    if (!global->command_list->redirections)
        return ;
    redirections = global->command_list->redirections;
    if (redirections->token == LEFT)
        handle_infile(redirections);
    else if (redirections->token == DOUBLE_LEFT)
        handle_heredoc(redirections);
    else if (redirections->token == RIGHT)
        handle_outfile(redirections);
    else if (redirections->token == RIGHT)
        handle_append(redirections);
    // else if (redirections->token == PIPE)
    //     handle_outfile(redirections);
}
