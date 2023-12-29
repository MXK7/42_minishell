/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arazzok <arazzok@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 21:50:36 by mpoussie          #+#    #+#             */
/*   Updated: 2023/12/29 13:37:13 by arazzok          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Test functions
void	print_lexer(t_lexer *head)
{
	t_lexer	*current;

	current = head;
	while (current)
	{
		ft_printf("Token: %s, Type: %d\n", current->str, current->token);
		current = current->next;
	}
}

void	parser(t_global *global)
{
	t_lexer	*token_list;

	token_list = NULL;
	token_list = tokenize(global->input);
	print_lexer(token_list);
	free_lexer(token_list);
	// 5. Gérer les pipes
	// 6. Gérer les redirections
	// 7. Gérer $? (code de sortie du dernier programme exécuté)
	// x. Gérer les variables d'environnement
}
