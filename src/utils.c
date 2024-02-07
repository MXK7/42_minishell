/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arazzok <arazzok@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 01:58:13 by mpoussie          #+#    #+#             */
/*   Updated: 2024/02/07 15:37:50 by arazzok          ###   ########.fr       */
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

static int	find_matching_quote(char *line, int i, int *nb_quote, char quote)
{
	int	j;

	j = i + 1;
	*nb_quote += 1;
	while (line[j] && line[j] != quote)
		j++;
	if (line[j] == quote)
		*nb_quote += 1;
	return (j - i);
}

int	are_quotes_closed(char *line)
{
	int	s_quote;
	int	d_quote;
	int	i;

	s_quote = 0;
	d_quote = 0;
	i = 0;
	while (line[i])
	{
		if (line[i] == '\'')
			i += find_matching_quote(line, i, &s_quote, '\'');
		if (line[i] == '"')
			i += find_matching_quote(line, i, &d_quote, '"');
		i++;
	}
	if ((s_quote > 0 && s_quote % 2 != 0) || (d_quote > 0 && d_quote % 2 != 0))
		return (0);
	return (1);
}

void	free_array(char **array)
{
	int	i;

	if (!array)
		return ;
	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}
