/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpoussie <mpoussie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 16:36:53 by mpoussie          #+#    #+#             */
/*   Updated: 2023/12/06 16:56:41 by mpoussie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sigintHandler(int signum __attribute__((unused)))
{
	printf("\n");
	rl_on_new_line();
	rl_redisplay();
}
