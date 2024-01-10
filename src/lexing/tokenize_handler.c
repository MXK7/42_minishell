/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_handler.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arazzok <arazzok@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/24 16:06:24 by arazzok           #+#    #+#             */
/*   Updated: 2024/01/10 22:08:06 by arazzok          ###   ########.fr       */
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
	char	*temp;
	int		len;

	len = 1;
	if (operator == '|')
		token = PIPE;
	else if ((operator == '<' || operator == '>') && operator == input[*i + 1])
	{
		len = 2;
		if (operator == '<')
			token = DOUBLE_LEFT;
		else if (operator == '>')
			token = DOUBLE_RIGHT;
	}
	else if (operator == '<')
		token = LEFT;
	else if (operator == '>')
		token = RIGHT;
	temp = ft_strndup(&input[*i], len);
	*current = init_lexer(temp, token);
	*i += len - 1;
	free(temp);
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
		*current = init_lexer(word, WORD);
		*i = j;
		free(word);
	}
}

void	handle_word(char *input, int *i, t_lexer **current)
{
	int		len;
	char	*word;

	len = get_word_len(input, *i);
	word = ft_strndup(&input[*i], len);
	*current = init_lexer(word, WORD);
	*i += len - 1;
	free(word);
}

void	handle_head(t_lexer **head, t_lexer *current)
{
	t_lexer	*temp;

	if (*head == NULL)
		*head = current;
	else
	{
		temp = *head;
		while (temp->next)
			temp = temp->next;
		temp->next = current;
		current->prev = temp;
		current->next = NULL;
	}
}
