/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpoussie <mpoussie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/16 23:11:22 by mpoussie          #+#    #+#             */
/*   Updated: 2023/05/01 04:09:33 by mpoussie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned int	strlen;
	unsigned int	i;
	char			*result;
	const char		*str;

	str = s;
	strlen = 0;
	while (str[strlen])
		strlen++;
	result = malloc(strlen + 1);
	if (result == NULL)
		return (NULL);
	i = 0;
	while (*str)
	{
		result[i] = f(i, *str);
		i++;
		str++;
	}
	result[strlen] = '\0';
	return (result);
}
