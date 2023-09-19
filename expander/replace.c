/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snaggara <snaggara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 15:53:58 by snaggara          #+#    #+#             */
/*   Updated: 2023/09/19 17:05:31 by snaggara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_replace_dollar(t_data *data, char **str)
{
	char	*dollar;
	char	*word;
	char	*replace_str;

	dollar = ft_strchr(*str, '$');
	while (dollar)
	{
		word = ft_extract_word(dollar);
		replace_str = ft_found_replace_value(data, word);
		*str = ft_replace(*str, dollar, replace_str);
		if (!*str)
			return (0);
		free(word);
		free(replace_str);
		dollar = ft_strchr(*str, '$');
	}
	return (1);
}

char	*ft_replace(char *str, char *dollar, char *replace_str)
{
	char	*to_return;
	int		i;
	int		j;
	int		k;

	to_return = ft_malloc_replace_char(str, replace_str);
	if (!to_return)
		return (0);
	i = -1;
	while (str + ++i != dollar)
		to_return[i] = str[i];
	j = -1;
	while (replace_str[++j])
		to_return[i + j] = replace_str[j];
	k = i + j;
	i++;
	while (str[i] && (str[i] != ' ' && str[i] != '$' && str[i] != '?'))
		i++;
	if (str[i] == '?')
		i++;
	while (str[i])
		to_return[k++] = str[i++];
	to_return[k] = '\0';
	free(str);
	return (to_return);
}

char	*ft_malloc_replace_char(char *str, char *replace_str)
{
	size_t	size;
	char	*to_return;

	size = ft_strlen(str) + ft_strlen(replace_str) + 1;
	to_return = (char *)malloc(sizeof(char) * size);
	if (!to_return)
		return (NULL);
	ft_bzero(to_return, size);
	return (to_return);
}

char	*ft_found_replace_value(t_data *data, char *word)
{
	int		i;
	char	*equal;
	char	*to_return;

	if (word[0] == '?')
		return (ft_itoa(data->exit_status));
	i = 0;
	while (data->secret_envp[i] && !ft_same_key(data->secret_envp[i], word))
		i++;
	if (!data->secret_envp[i])
	{
		to_return = (char *)malloc(sizeof(char));
		to_return[0] = '\0';
		if (!to_return)
			return (NULL);
		return (to_return);
	}
	equal = ft_strchr(data->secret_envp[i], '=');
	if (!equal)
		return (NULL);
	return (ft_strdup(equal + 1));
}

char	*ft_extract_word(char *str)
{
	int		i;
	int		j;
	char	*word;

	i = 1;
	j = 0;
	if (str[0] != '$')
		return (NULL);
	while (str[i] && (str[i] != ' ' && str[i] != '$'))
		i++;
	word = (char *)malloc(sizeof(char) * (i + 1));
	if (!word)
		return (NULL);
	while (j < i - 1)
	{
		word[j] = str[j + 1];
		j++;
	}
	word[j] = '\0';
	return (word);
}
