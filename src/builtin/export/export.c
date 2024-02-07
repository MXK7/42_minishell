/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpoussie <mpoussie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 00:44:20 by mpoussie          #+#    #+#             */
/*   Updated: 2024/02/07 01:24:35 by mpoussie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_key_good_format(char *str)
{
	while (*str)
	{
		if (*str != '_' && !ft_isalnum(*str))
			return (false);
		str++;
	}
	return (true);
}

void	print_invalid_identifier(char *id)
{
	ft_putstr_fd("ams: export: `", 2);
	ft_putstr_fd(id, 2);
	ft_putstr_fd("': not a valid identifier\n'", 2);
}

static int	insert_single_env_var(t_global *global)
{
	bool	good_format;
	int		i;
	char	**arguments;

	arguments = global->command_list->str;
	good_format = true;
	i = 1;
	while (i <= 2)
	{
		if (!ft_isalpha(arguments[i][0]) && arguments[i][0] != '_')
		{
			good_format = false;
			print_invalid_identifier(arguments[i]);
		}
		else if (!is_key_good_format(arguments[i]))
		{
			good_format = false;
			print_invalid_identifier(arguments[i]);
		}
		i++;
	}
	if (good_format)
		edit_env(global, arguments[1], arguments[2]);
	return (!good_format);
}

static int	insert_multiple_env_var(t_global *global)
{
	size_t	i;
	int		res;
	char	**arguments;

	arguments = global->command_list->str;
	i = 1;
	res = 0;
	while (arguments[i])
	{
		res |= parse_env_var_data(arguments[i], global);
		i++;
	}
	return (res);
}

int	_builtin_export(t_global *global)
{
	char	**arguments;

	arguments = global->command_list->str;
	if (arguments[1] == NULL)
		return (print_env_sorted(global->env));
	else
	{
		if (ft_strs_len(arguments) == 3 && ft_strchr(arguments[1], '=') == NULL
			&& ft_strchr(arguments[2], '=') == NULL)
			return (insert_single_env_var(global));
		else
			return (insert_multiple_env_var(global));
	}
}
