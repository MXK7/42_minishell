/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_multiple_env.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpoussie <mpoussie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 00:44:08 by mpoussie          #+#    #+#             */
/*   Updated: 2024/02/07 05:44:56 by mpoussie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	set_env_var_data(char *key, char *value, t_global *global,
				bool append);
static char	*detect_sep(char *argument, bool *append);
static void	parse_env_var_free(char *argument, int res);

int	parse_env_var_data(char *argument, t_global *global)
{
	char	*sep;
	bool	append;
	int		res;

	if (!ft_isalpha(argument[0]) && argument[0] != '_')
	{
		print_invalid_identifier(argument);
		return (1);
	}
	sep = detect_sep(argument, &append);
	if (!is_key_good_format(argument))
	{
		if (sep)
			*sep = '=';
		if (sep && append)
			*(sep - 1) = '+';
		print_invalid_identifier(argument);
		return (1);
	}
	res = set_env_var_data(argument, sep, global, append);
	if (res)
		parse_env_var_free(argument, res);
	return (res);
}

static int	set_env_var_data(char *key, char *value, t_global *global,
		bool append)
{
	char	*prev_env_var;

	if (append)
		prev_env_var = get_env(key, global);
	if (value)
		value += 1;
	if (append && prev_env_var)
	{
		if (value)
		{
			value = ft_strjoin(prev_env_var, value);
			free(prev_env_var);
			if (value)
			{
				edit_env(global, key, value);
				free(value);
			}
			else
				return (ENOMEM);
		}
	}
	else
		edit_env(global, key, value);
	return (0);
}

static char	*detect_sep(char *argument, bool *append)
{
	char	*sep;

	*append = false;
	sep = ft_strchr(argument, '=');
	if (sep)
	{
		*sep = 0;
		if (*(sep - 1) == '+')
		{
			*append = true;
			*(sep - 1) = 0;
		}
	}
	return (sep);
}

static void	parse_env_var_free(char *argument, int res)
{
	ft_putstr_fd("ams: export: `", 2);
	ft_putstr_fd(argument, 2);
	ft_putstr_fd("': ", 2);
	ft_putstr_fd(strerror(res), 2);
	ft_putstr_fd("\n", 2);
}
