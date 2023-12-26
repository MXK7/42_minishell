/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpoussie <mpoussie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/22 14:25:43 by arazzok           #+#    #+#             */
/*   Updated: 2023/12/26 07:55:49 by mpoussie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_lexer	*init_lexer(char *str, t_token token, int index)
{
	t_lexer	*node;

	node = malloc(sizeof(t_lexer));
	if (!node)
		return (NULL);
	node->str = ft_strdup(str);
	node->token = token;
	node->index = index;
	node->prev = NULL;
	node->next = NULL;
	return (node);
}

void	free_lexer(t_lexer *head)
{
	t_lexer	*temp;

	while (head)
	{
		temp = head;
		head = head->next;
		free(temp->str);
		free(temp);
	}
}

t_lexer	*tokenize(char *input)
{
	t_lexer	*head;
	t_lexer	*current;
	int		len;
	int		i;

	head = NULL;
	current = NULL;
	len = ft_strlen(input);
	i = 0;
	while (i < len)
	{
		skip_whitespaces(input, i);
		if (is_operator(input[i]))
			handle_operator(input, &i, &current, input[i]);
		else if (is_quote(input[i]))
			handle_quote(input, &i, &current, input[i]);
		else
			handle_word(input, &i, &current input[i]);
		// TODO: à mettre dans une fonction à part
		if (head == NULL)
			head = current;
		else
		{
			current->prev = head;
			head->next = current;
			head = current;
		}
		i++;
	}
	return (head);
}
