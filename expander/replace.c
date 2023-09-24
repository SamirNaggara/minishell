/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snaggara <snaggara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 15:53:58 by snaggara          #+#    #+#             */
/*   Updated: 2023/09/24 20:53:24 by snaggara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

int	ft_add_expand_word(t_data *data, int *state, int *i)
{
	char	*value;

	value = ft_itoa(data->exit_status);
	if (!value)
		return (0);
	data->new_word = ft_strjoin_custom(data->new_word, value);
	if (!data->new_word)
		return (free(value), 0);
	*state = 1;
	(i)++;
	return (1);
}

char	*ft_extract_word(char *str)
{
	int		i;
	char	*word;

	if (!str || !*str)
		return (NULL);
	word = (char *)malloc(sizeof(char));
	if (!word)
		return (NULL);
	word[0] = '\0';
	i = 1;
	while (str[i] && !ft_char_is_stop_dollar(str[i]))
	{
		word = ft_join_char(word, str[i]);
		i++;
	}
	return (word);
}

char	*ft_join_char(char *str, char c)
{
	char	*new;
	int		size;
	int		i;

	i = 0;
	if (!str)
	{
		new = (char *)malloc(sizeof(char) * 2);
		new[0] = c;
		new[1] = '\0';
		return (new);
	}
	size = ft_strlen(str) + 2;
	new = (char *)malloc(sizeof(char) * size);
	if (!new)
		return (0);
	while (str[i])
	{
		new[i] = str[i];
		i++;
	}
	new[i] = c;
	new[i + 1] = '\0';
	free(str);
	return (new);
}
