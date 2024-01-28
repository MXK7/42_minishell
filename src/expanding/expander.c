/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arazzok <arazzok@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 12:51:31 by arazzok           #+#    #+#             */
/*   Updated: 2024/01/28 01:39:31 by arazzok          ###   ########.fr       */
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

	len = ft_strlen(result) - (end - start + 1) + ft_strlen(value);
	new = malloc(sizeof(char) * (len + 1));
	if (!new)
		return (NULL);
	ft_strncpy(new, result, start - result);
	new[start - result] = '\0';
	ft_strcat(new, value);
	ft_strcat(new, end + 1);
	free(result);
	return (new);
}

static void process_expand(char **start, char **result, bool is_quote, char **end)
{
    char    *name;
    char    *value;

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

    is_quote = false;
    result = ft_strdup(command);
    start = result;
    while (*start)
    {
        if (*start == '\"')
            is_quote = !is_quote;
        else
            process_expand(&start, &result, is_quote, &end);
        start++;
    }
    return (result);
}
