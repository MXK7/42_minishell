/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpoussie <mpoussie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 16:36:53 by mpoussie          #+#    #+#             */
/*   Updated: 2023/12/05 21:51:47 by mpoussie         ###   ########.fr       */
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
