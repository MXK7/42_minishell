/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpoussie <mpoussie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 01:40:46 by mpoussie          #+#    #+#             */
/*   Updated: 2024/02/07 15:19:38 by mpoussie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	_builtin_pwd(t_global *global)
{
	free(global->pwd);
	global->pwd = getcwd(NULL, 1024);
	ft_printf("%s\n", global->pwd);
	return (0);
}
