/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arazzok <arazzok@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 18:23:53 by arazzok           #+#    #+#             */
/*   Updated: 2024/01/10 19:14:05 by arazzok          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_error(int err_code, t_global *global)
{
	(void)global;
	if (err_code == 1)
		ft_putendl_fd("Error.\nQuotes are note closed.", STDERR_FILENO);
	// free_global(global);
	return (1);
}
