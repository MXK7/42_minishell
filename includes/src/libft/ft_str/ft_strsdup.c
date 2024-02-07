/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsdup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpoussie <mpoussie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 00:53:44 by mpoussie          #+#    #+#             */
/*   Updated: 2024/02/07 01:03:23 by mpoussie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_strs_dup(char **src)
{
	char	**dest;
	size_t	dest_len;
	size_t	i;

	dest_len = ft_strs_len(src);
	dest = malloc((dest_len + 1) * sizeof(char *));
	if (!dest)
		return (NULL);
	i = 0;
	while (i < dest_len)
	{
		dest[i] = ft_strdup(src[i]);
		if (!dest[i])
		{
			ft_free_strs(dest);
			return (NULL);
		}
		i++;
	}
	dest[i] = NULL;
	return (dest);
}
