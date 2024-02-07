/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpoussie <mpoussie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 12:51:31 by arazzok           #+#    #+#             */
/*   Updated: 2024/02/07 17:46:56 by mpoussie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*find_env_var(char *start, char **end)
{
	start = ft_strchr(start, '$');
	if (start)
	{
		*end = start + 1;
		if (**end == '?')
		{
			(*end)++;
			return (ft_strdup("?"));
		}
		while (ft_isalnum(**end) || **end == '_')
			(*end)++;
		return (ft_strndup(start + 1, *end - start - 1));
	}
	return (NULL);
}

static char	*get_env_var_value(char *name, t_global *global)
{
	char	*value;

	if (ft_strcmp(name, "?") == 0)
	{
		value = ft_itoa(g_exit_status);
		if (value)
			return (value);
	}
	value = get_env(name, global);
	if (!value)
		value = ft_strdup("");
	return (value);
}

static char	*replace_env_var(char *result, char *start, char *end, char *value)
{
	char	*new;
	size_t	len;
	size_t	start_offset;
	char	*end_copy;

	end_copy = ft_strdup(end);
	start_offset = start - result;
	len = start_offset + ft_strlen(value) + ft_strlen(end_copy);
	new = malloc(sizeof(char) * (len + 1));
	if (!new)
	{
		free(end_copy);
		return (NULL);
	}
	ft_strncpy(new, result, start_offset);
	new[start_offset] = '\0';
	ft_strcat(new + start_offset, value);
	ft_strcat(new + start_offset + ft_strlen(value), end_copy);
	new[len] = '\0';
	free(result);
	free(end_copy);
	return (new);
}

static void	process_expand(char **start, char **result, char **end,
		t_global *global)
{
	char	*name;
	char	*value;

	if (**start == '$')
	{
		if (is_whitespace(*(*start + 1)) || *(*start + 1) == '\0')
		{
			(*start)++;
			return ;
		}
		name = find_env_var(*start, end);
		if (name)
		{
			value = get_env_var_value(name, global);
			*result = replace_env_var(*result, *start, *end, value);
			*start = *result + (*start - *result) + ft_strlen(value);
			free(name);
			free(value);
		}
	}
}

char	*expand_env_var(char *command, t_global *global)
{
	char	*result;
	char	*start;
	char	*end;
	size_t	offset;

	result = ft_strdup(command);
	start = result;
	while (*start)
	{
		offset = start - result;
		process_expand(&start, &result, &end, global);
		start = result + offset;
		if (*start)
			start++;
	}
	return (result);
}
