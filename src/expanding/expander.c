/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arazzok <arazzok@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 12:51:31 by arazzok           #+#    #+#             */
/*   Updated: 2024/01/29 20:11:40 by arazzok          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*find_env_var(char *start, char **end)
{
	start = ft_strchr(start, '$');
	if (start)
	{
		*end = start + 1;
		while (ft_isalnum(**end) || **end == '_')
			(*end)++;
		return (ft_strndup(start + 1, *end - start - 1));
	}
	return (NULL);
}

static char	*get_env_var_value(char *name)
{
	char	*value;

	value = getenv(name);
	if (!value)
		value = "";
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

static void	process_expand(char **start, char **result, bool is_quote,
		char **end)
{
	char	*name;
	char	*value;

	if (**start == '$' && !is_quote)
	{
		name = find_env_var(*start, end);
		if (name)
		{
			value = get_env_var_value(name);
			*result = replace_env_var(*result, *start, *end, value);
			*start = *result + (*start - *result) + ft_strlen(value);
			free(name);
		}
	}
}

char	*expand_env_var(char *command)
{
	char	*result;
	char	*start;
	char	*end;
	bool	is_quote;
	size_t	offset;

	is_quote = false;
	result = ft_strdup(command);
	start = result;
	while (*start)
	{
		if (*start == '\"')
			is_quote = !is_quote;
		else
		{
			offset = start - result;
			process_expand(&start, &result, is_quote, &end);
			start = result + offset;
		}
		start++;
	}
	return (result);
}
