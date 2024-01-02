/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpoussie <mpoussie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 01:58:13 by mpoussie          #+#    #+#             */
/*   Updated: 2023/12/29 18:12:27 by mpoussie         ###   ########.fr       */
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
