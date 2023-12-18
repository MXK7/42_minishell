/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpoussie <mpoussie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 01:58:13 by mpoussie          #+#    #+#             */
/*   Updated: 2023/12/18 20:05:11 by mpoussie         ###   ########.fr       */
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

char	**split_string(const char *str, int *numWords)
{
	char	**words;
	char	*token;
	char	*str_copy;

	words = (char **)malloc(strlen(str) * sizeof(char *));
	if (words == NULL)
		exit(EXIT_FAILURE);
	str_copy = strdup(str);
	if (str_copy == NULL)
		exit(EXIT_FAILURE);
	token = strtok(str_copy, " ");
	*numWords = 0;
	while (token != NULL)
	{
		words[*numWords] = strdup(token);
		if (words[*numWords] == NULL)
			exit(EXIT_FAILURE);
		(*numWords)++;
		token = strtok(NULL, " ");
	}
	free(str_copy);
	return (words);
}

// TODO:: Create function for free all allocation in memory.
// free(path_tokens);