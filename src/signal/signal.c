/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpoussie <mpoussie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 01:39:31 by mpoussie          #+#    #+#             */
/*   Updated: 2024/01/03 12:13:27 by mpoussie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	_signal_exit(int signal __attribute__((unused)), t_global *global)
{
	char	buffer[1024];
	ssize_t	bytesRead;

	bytesRead = read(STDIN_FILENO, buffer, sizeof(buffer));
	if (bytesRead == 0)
		exit_requested = false;
	else if (bytesRead < 0)
		exit_requested = false;
	(void)global;
	exit(-1);
}

void	_signal_newline(int signal __attribute__((unused)))
{
	if (signal == 2)
	{
		rl_replace_line("", 0);
		write(1, "\n", 1);
		rl_on_new_line();
		rl_redisplay();
		return ;
	}
	exit_requested = false;
	exit(-1);
}
