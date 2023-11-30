/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpoussie <mpoussie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 06:17:50 by mpoussie          #+#    #+#             */
/*   Updated: 2023/05/01 04:09:09 by mpoussie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static size_t	ft_count_words(char const *str, char c)
{
	size_t	count;

	count = 0;
	while (*str)
	{
		if (*str != c && (*(str + 1) == c || *(str + 1) == '\0'))
			count++;
		str++;
	}
	return (count);
}

static char	*ft_get_next_word(char const **s, char c)
{
	char	*word;
	size_t	len;

	while (**s == c)
		(*s)++;
	len = 0;
	while ((*s)[len] && (*s)[len] != c)
		len++;
	word = ft_substr(*s, 0, len);
	if (word == NULL)
		return (NULL);
	(*s) += len;
	return (word);
}

static void	ft_free_split(char **str, int i)
{
	while (i-- > 0)
		free(str[i]);
	free(str);
}

char	**ft_split(char const *s, char c)
{
	char	**split;
	size_t	count;
	size_t	i;

	if (!s)
		return (NULL);
	count = ft_count_words(s, c);
	split = (char **)ft_calloc(count + 1, sizeof(char *));
	if (split == NULL)
		return (NULL);
	i = 0;
	while (i < count)
	{
		split[i] = ft_get_next_word(&s, c);
		if (split[i] == NULL)
		{
			ft_free_split(split, i);
			return (NULL);
		}
		i++;
	}
	return (split);
}
