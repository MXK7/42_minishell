/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arazzok <arazzok@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/22 14:52:44 by arazzok           #+#    #+#             */
/*   Updated: 2023/12/22 16:22:15 by arazzok          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int is_whitespace(char c)
{
    return (c == ' ' || (c > 8 && c < 14));
}

int is_operator(char c)
{
    return (c == '|' || c == '<' || c == '>');
}

void skip_whitespaces(char *input, int *i)
{
    while (is_whitespace(input[*i]))
        (*i)++;
}
