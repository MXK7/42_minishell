/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arazzok <arazzok@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/26 07:38:31 by mpoussie          #+#    #+#             */
/*   Updated: 2024/01/23 13:28:43 by arazzok          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	tri_export_var(t_global *global);

int	_builtin_export(t_global *global)
{
	int	i;

	i = 0;
	tri_export_var(global);
	while (global->env[i])
	{
		if (global->env[i][0] != '\0')
			printf("declare -x %s\n", global->env[i]);
		i++;
	}
	return (0);
}

static void	tri_export_var(t_global *global)
{
	int		i;
	int		x;
	char	*temp;

	i = 0;
	x = 0;
	temp = malloc(sizeof(char *) * 9999);
	while (global->env[i + 1])
	{
		x = i + 1;
		if (global->env[i][0] > global->env[x][0])
		{
			temp = global->env[i];
			global->env[i] = global->env[x];
			global->env[x] = temp;
			i = 0;
		}
		i++;
	}
	free(temp);
	temp = NULL;
}
