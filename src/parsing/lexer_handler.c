/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpoussie <mpoussie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/24 16:06:24 by arazzok           #+#    #+#             */
/*   Updated: 2023/12/27 08:41:12 by mpoussie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*ft_strndup(const char *src, size_t size)
{
	size_t	len;
	char	*copy;

	len = 0;
	while (src[len] && len < size)
		len++;
	copy = malloc(sizeof(char) * (len + 1));
	if (!copy)
		return (NULL);
	ft_memcpy(copy, src, size);
	copy[len] = '\0';
	return (copy);
}

void	handle_operator(char *input, int *i, t_lexer **current, char operator)
{
	t_token	token;

	if (operator == '|')
		token = PIPE;
	else if (operator == '<')
		token = LEFT;
	else if (operator == '>')
		token = RIGHT;
	*current = init_lexer(&input[*i], token, *i);
}

void	handle_quote(char *input, int *i, t_lexer **current, char quote)
{
	char	*word;
	int		j;

	j = *i + 1;
	while (input[j] && input[j] != quote)
		j++;
	if (input[j] == quote)
	{
		word = ft_strndup(&input[*i + 1], j - *i - 1);
		*current = init_lexer(word, WORD, *i);
		*i = j;
	}
	else
	{
		// * Quote non-fermée
		// ? Ignorer ou gérer l'erreur ?
	}
}

void	handle_word(char *input, int *i, t_lexer **current)
{
	int		len;
	char	*word;

	len = get_word_len(input, *i);
	word = ft_strndup(&input[*i], len);
	*current = init_lexer(word, WORD, *i);
	*i += len - 1;
}
