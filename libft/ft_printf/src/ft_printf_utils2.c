/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpoussie <mpoussie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 06:26:44 by mpoussie          #+#    #+#             */
/*   Updated: 2023/05/01 04:08:03 by mpoussie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft.h"

int	ft_num_len(unsigned int nbr)
{
	int	len;

	len = 0;
	while (nbr != 0)
	{
		len++;
		nbr /= 10;
	}
	return (len);
}

char	*ft_unsigned_itoa(unsigned int nbr)
{
	int		len;
	char	*alpha;

	len = ft_num_len(nbr);
	alpha = malloc(sizeof(char) * (len + 1));
	if (!alpha)
		return (NULL);
	alpha[len] = '\0';
	while (nbr != 0)
	{
		alpha[len - 1] = (nbr % 10) + 48;
		nbr /= 10;
		len--;
	}
	return (alpha);
}

void	ft_put_hex(unsigned int nbr, const char format)
{
	if (nbr >= 16)
	{
		ft_put_hex(nbr / 16, format);
		ft_put_hex(nbr % 16, format);
	}
	else
	{
		if (nbr <= 9)
			ft_print_char(nbr + '0');
		else
		{
			if (format == 'x')
				ft_print_char(nbr - 10 + 'a');
			if (format == 'X')
				ft_print_char(nbr - 10 + 'A');
		}
	}
}
