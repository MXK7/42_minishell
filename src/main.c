/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpoussie <mpoussie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 14:21:38 by mpoussie          #+#    #+#             */
/*   Updated: 2023/12/01 00:29:03 by mpoussie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

jmp_buf	env;

void	sigintHandler(int signum __attribute__((unused)))
{
	printf("\n");
	rl_on_new_line();
	rl_redisplay();
}

int	main(void)
{
	char *pwd;
	char *rl;
	int exitRequested;

	signal(SIGINT, sigintHandler);
	exitRequested = 0;
	while (!exitRequested)
	{
		if (setjmp(env) == 0)
		{
			rl = readline("Minishell > ");

			if (ft_strcmp(rl, "exit") == 0)
				exitRequested = 1;
			else if (ft_strcmp(rl, "pwd") == 0)
			{
				pwd = getcwd(NULL, 0);
				printf("%s\n", pwd);
			}
		}
	}
	free(pwd);
	return (0);
}