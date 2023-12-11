/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpoussie <mpoussie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 01:40:46 by mpoussie          #+#    #+#             */
/*   Updated: 2023/12/08 21:45:26 by mpoussie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	_builtin_pwd(t_global *global)
{
	global->pwd = getcwd(NULL, 0);
	printf("%s\n", global->pwd);
}
