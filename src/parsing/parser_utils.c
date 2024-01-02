/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arazzok <arazzok@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 11:31:55 by arazzok           #+#    #+#             */
/*   Updated: 2024/01/02 16:41:20 by arazzok          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_redirection(t_token token)
{
	return (token == LEFT || token == DOUBLE_LEFT || token == RIGHT
		|| token == DOUBLE_RIGHT);
}

int	get_str_size(char **str)
{
	int	size;

	if (!str)
		return (0);
	size = 0;
	while (str[size])
		size++;
	return (size);
}
