/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgoigoux <sgoigoux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 15:00:56 by snaggara          #+#    #+#             */
/*   Updated: 2023/09/16 15:43:49 by sgoigoux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
	Permet d'ajouter une chaine de caractere a la fin
	du secret env
	Pour ça il faut la reconstuire et la free
*/
int	ft_add_one_envp(t_data *data, char *str)
{
	int		size;
	char	**new_envp;
	int		i;

	size = ft_size_tab(data->secret_envp);
	new_envp = (char **)malloc(sizeof(char *) * (size + 2));
	if (!new_envp)
		return (0);
	i = 0;
	while (data->secret_envp[i])
	{
		new_envp[i] = data->secret_envp[i];
		i++;
	}
	new_envp[i] = ft_strdup(str);
	if (!new_envp[i])
		return (0);
	new_envp[i + 1] = NULL;
	free(data->secret_envp);
	data->secret_envp = new_envp;
	return (1);
}

/*
	Si on fait export tout seul
	Alors on doit tout imprimer
*/

int	ft_strcmp(const char *s1, const char *s2)
{
	while (*s1 && (*s1 == *s2))
	{
		s1++;
		s2++;
	}
	return (*(const unsigned char *)s1 - *(const unsigned char *)s2);
}

void	ft_print_all_export(t_data *data)
{
	int		i;
	int		j;
	int		count;
	char	*current;

	i = 1;
	count = 0;
	while (data->secret_envp[count])
		count++;
	while (i < count)
	{
		current = data->secret_envp[i];
		j = i - 1;
		while (j >= 0 && ft_strcmp(data->secret_envp[j], current) > 0)
		{
			data->secret_envp[j + 1] = data->secret_envp[j];
			j--;
		}
		data->secret_envp[j + 1] = current;
		i++;
	}
	i = 0;
	while (data->secret_envp[i])
	{
		if (ft_strnstr(data->secret_envp[i], \
		"=/usr/bin/env", 14) != data->secret_envp[i])
			ft_print_one_export(data->secret_envp[i]);
		i++;
	}
}

/*
	On imprime une ligne avec le format export
*/
void	ft_print_one_export(char *line)
{
	int	i;

	i = 0;
	write(1, "export ", 7);
	while (line[i] && line[i] != '=')
		write(1, line + i++, 1);
	if (!line[i])
	{
		write(1, "\n", 1);
		return ;
	}
	write(1, line + i++, 1);
	write(1, "\"", 1);
	while (line[i])
		write(1, line + i++, 1);
	write(1, "\"", 1);
	write(1, "\n", 1);
}
