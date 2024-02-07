/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arazzok <arazzok@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 22:38:03 by mpoussie          #+#    #+#             */
/*   Updated: 2024/02/06 21:23:24 by arazzok          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *src)
{
	char	*dest;
	size_t	i;
	size_t	strlen;

	if (src == NULL)
		return (NULL);
	strlen = ft_strlen(src);
	dest = (char *)malloc(sizeof(*dest) * (strlen + 1));
	if (!dest)
		return (NULL);
	i = 0;
	while (i < strlen)
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}
