/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpoussie <mpoussie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 10:18:31 by mpoussie          #+#    #+#             */
/*   Updated: 2023/12/22 14:21:58 by mpoussie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	_builtin_cd(t_global *global)
{
    int fd;
    printf("%s\n%s", global->args_path[0], global->args_path[1])
    // opendir: verifie si le chemin d'acces existe
    if (opendir(global->args_path[1]) != NULL)
    {
        fd = open(global->args_path[1], O_RDONLY);
        if (fd != -1)
        {
            printf("GOOD");
            // TODO: 
        }
    }
    // chdir: se conduit vers le chemin d'acces

    // TODO update_env: PWD change vers le new chemin d'acces
}
