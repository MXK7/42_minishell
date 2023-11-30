/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_function.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpoussie <mpoussie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 06:09:42 by mpoussie          #+#    #+#             */
/*   Updated: 2023/05/01 04:07:56 by mpoussie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft.h"

int	ft_print_percent(void)
{
	write(1, "%", 1);
	return (1);
}

int	ft_print_char(int str)
{
	write(1, &str, 1);
	return (1);
}

int	ft_print_str(char *str)
{
	int	i;

	i = 0;
	if (str == NULL)
	{
		ft_put_str("(null)");
		return (6);
	}
	while (str[i])
	{
		write(1, &str[i], 1);
		i++;
	}
	return (i);
}

int	ft_print_nbr(int nbr)
{
	int		len;
	char	*itoa;

	len = 0;
	itoa = ft_itoa(nbr);
	len = ft_print_str(itoa);
	free(itoa);
	return (len);
}

int	ft_print_ptr(unsigned long long ptr)
{
	int	print_len;

	print_len = 0;
	if (!ptr)
	{
		write(1, "(nil)", 5);
		return (5);
	}
	print_len += write(1, "0x", 2);
	if (ptr == 0)
		print_len += write(1, "0", 1);
	else
	{
		ft_put_ptr(ptr);
		print_len += ft_printf_len(ptr);
	}
	return (print_len);
}
