/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arazzok <arazzok@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 21:50:36 by mpoussie          #+#    #+#             */
/*   Updated: 2023/12/22 12:08:29 by arazzok          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parser(t_global *global)
{
    (void)global;
    // 1. Tokenization (classer global->input en tokens)
	
    // 2. Gérer les caractères d'espace (espaces, tab, new line...)

    // 3. Gérer les quotes (ne traiter aucun caractère spécial à l'intérieur)
    
    // 4. Gérer les double quotes (ne traiter aucun caractère spécial à l'intérieur sauf $)
    
    // 5. Gérer les pipes

    // 6. Gérer les redirections

    // 7. Gérer $? (code de sortie du dernier programme exécuté)

    // x. Gérer les variables d'environnement	
}
