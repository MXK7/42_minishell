/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpoussie <mpoussie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 06:57:10 by mpoussie          #+#    #+#             */
/*   Updated: 2023/05/01 04:09:54 by mpoussie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static size_t	ft_len(int n)
{
	size_t	i;

	i = 0;
	if (n == 0)
		return (1);
	if (n < 0)
		i++;
	while (n != 0)
	{
		n = n / 10;
		i++;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	unsigned int	nbr;
	long int		len;
	char			*alpha;

	len = ft_len(n);
	if (n < 0)
		nbr = -n;
	else
		nbr = n;
	alpha = malloc(sizeof(char) * len + 1);
	if (!alpha)
		return (NULL);
	if (n == 0)
		alpha[0] = '0';
	alpha[len] = '\0';
	len--;
	while (nbr)
	{
		alpha[len--] = (nbr % 10) + '0';
		nbr /= 10;
	}
	if (n < 0)
		alpha[0] = '-';
	return (alpha);
}
