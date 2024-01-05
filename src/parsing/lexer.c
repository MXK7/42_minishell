/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arazzok <arazzok@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/22 14:25:43 by arazzok           #+#    #+#             */
/*   Updated: 2024/01/05 19:28:02 by arazzok          ###   ########.fr       */
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

void	del_one(t_lexer **target)
{
	t_lexer *tmp;

    tmp = *target;
    if (tmp->prev)
        tmp->prev->next = tmp->next;
    if (tmp->next)
        tmp->next->prev = tmp->prev;
    free(tmp->str);
    free(tmp);
    *target = NULL;
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
		skip_whitespaces(input, &i);
		if (is_operator(input[i]))
			handle_operator(input, &i, &current, input[i]);
		else if (is_quote(input[i]))
			handle_quote(input, &i, &current, input[i]);
		else
			handle_word(input, &i, &current);
		handle_head(&head, current);
		i++;
	}
	return (head);
}
