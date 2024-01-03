/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpoussie <mpoussie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 01:58:13 by mpoussie          #+#    #+#             */
/*   Updated: 2024/01/03 11:46:54 by mpoussie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_path(char *path)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (path[i] != '\0')
	{
		if (path[i] == ':')
			count++;
		i++;
	}
	count++;
	return (count);
}

void free_minishell(t_global *global)
{
	int i;

	i = 0;
	while (global->env[i])
	{
		free(global->env[i]);
		i++;
	}
	i = 0;
	while (global->args_path[i])
	{
		free(global->args_path[i]);
		i++;
	}
	free(global->path);
	free(global->token);
	free(global);
}