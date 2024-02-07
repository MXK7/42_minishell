/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_handler.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arazzok <arazzok@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/24 16:06:24 by arazzok           #+#    #+#             */
/*   Updated: 2024/02/07 16:39:34 by arazzok          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strndup(const char *src, size_t size)
{
	size_t	len;
	char	*copy;

	len = ft_strlen(src);
	if (size < len)
		len = size;
	copy = malloc(sizeof(char) * (len + 1));
	if (!copy)
		return (NULL);
	ft_memcpy(copy, src, len);
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

void	handle_word(char *input, int *i, t_lexer **current, t_global *global)
{
	int		len;
	char	*word;
	char	*expanded_word;

	len = get_word_len(input, *i);
	word = ft_strndup(&input[*i], len);
	expanded_word = expand_env_var(word, global);
	*current = init_lexer(expanded_word, WORD);
	*i += len - 1;
	free(word);
	free(expanded_word);
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
