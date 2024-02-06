/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arazzok <arazzok@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 02:28:12 by arazzok           #+#    #+#             */
/*   Updated: 2024/02/06 15:50:34 by arazzok          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strncpy(char *dest, char *src, size_t len)
{
	size_t	i;

	i = 0;
	while (src[i] && i < len)
	{
		dest[i] = src[i];
		i++;
	}
	while (i < len)
		dest[i++] = '\0';
	return (dest);
}

void	call_expander(t_global *global)
{
	char	**strs;
	char	*expanded_str;
	int		i;

	strs = global->command_list->str;
	i = 0;
	if (!strs[i])
		strs[i] = ft_strdup("");
	while (strs[i])
	{
		expanded_str = expand_env_var(strs[i]);
		if (!expanded_str)
			return ;
		free(strs[i]);
		strs[i] = expanded_str;
		i++;
	}
}
