/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpoussie <mpoussie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 20:52:50 by arazzok           #+#    #+#             */
/*   Updated: 2024/02/06 21:20:47 by mpoussie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_single_quote(char *input, int *i, t_lexer **current, char quote)
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

void	handle_double_quotes(char *input, int *i, t_lexer **current, char quote)
{
	char	*expanded_word;
	char	*word;
	int		j;

	j = *i + 1;
	while (input[j] && input[j] != quote)
		j++;
	if (input[j] == quote)
	{
		word = ft_strndup(&input[*i + 1], j - *i - 1);
		expanded_word = expand_env_var(word);
		*current = init_lexer(expanded_word, WORD);
		*i = j;
		free(word);
	}
}
