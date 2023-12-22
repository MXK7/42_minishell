/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arazzok <arazzok@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/22 14:25:43 by arazzok           #+#    #+#             */
/*   Updated: 2023/12/22 16:09:23 by arazzok          ###   ########.fr       */
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
}

// Test functions
void	printLexer(Lexer *head)
{
	while (head)
	{
		ft_printf("Token: %s, Type: %d\n", head->str, head->token);
		head = head->next;
	}
}
