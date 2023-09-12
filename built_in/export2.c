/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snaggara <snaggara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 15:00:56 by snaggara          #+#    #+#             */
/*   Updated: 2023/09/06 15:01:32 by snaggara         ###   ########.fr       */
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
	char 	**new_envp;
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
void	ft_print_all_export(t_data *data)
{
	int	i;

	i = 0;
	while (data->secret_envp[i])
		ft_print_one_export(data->secret_envp[i++]);
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
