/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arazzok <arazzok@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/22 14:52:44 by arazzok           #+#    #+#             */
/*   Updated: 2024/02/06 21:05:06 by arazzok          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_whitespace(char c)
{
	return (c == ' ' || (c > 8 && c < 14));
}

int	is_operator(char c)
{
	return (c == '|' || c == '<' || c == '>');
}

int	is_quote(char c)
{
	return (c == '"' || c == '\'');
}

void	skip_whitespaces(char *input, int *i)
{
	while (is_whitespace(input[*i]))
		(*i)++;
}

int	get_word_len(char *input, int i)
{
	int	j;

	j = i;
	while (input[j] && !is_whitespace(input[j]) && !is_operator(input[j])
		&& !is_quote(input[j]))
		j++;
	return (j - i);
}
