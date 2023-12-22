/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpoussie <mpoussie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 10:18:31 by mpoussie          #+#    #+#             */
/*   Updated: 2023/12/22 18:26:33 by mpoussie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	_builtin_cd(t_global *global)
{
	int		fd;
	char	*new_pwd;

	// printf("%s\n%s\n", global->argv[0], global->argv[1]);
	// opendir: verifie si le chemin d'acces existe
	if (opendir(global->argv[1]) != NULL)
	{
		fd = open(global->argv[1], O_RDONLY);
		if (fd != -1)
		{
            // ! PEUT ETRE UN JOUR SA NOUS SERVIRA IN SHA ALLAH..
			new_pwd = ft_strjoin(_env_get("PWD=", global), ft_strjoin("/", global->argv[1]));
			// printf("NEW_PWD:%s\n", new_pwd);
            // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
            if (chdir(global->argv[1]) == 0)
                _update_env(global, "PWD", new_pwd);
            else
				printf("ERROR CD\n");
		}
	}    
}
