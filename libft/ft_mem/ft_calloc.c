/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpoussie <mpoussie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/16 10:18:40 by mpoussie          #+#    #+#             */
/*   Updated: 2023/05/01 04:10:27 by mpoussie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	size_t	result;
	char	*ret;

	result = count * size;
	ret = malloc(result);
	if (!ret)
		return (NULL);
	ft_bzero(ret, result);
	return (ret);
}
