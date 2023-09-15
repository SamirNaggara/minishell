/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snaggara <snaggara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 15:00:56 by snaggara          #+#    #+#             */
/*   Updated: 2023/09/15 15:41:04 by snaggara         ###   ########.fr       */
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
int	ft_print_all_export(t_data *data)
{
	int		i;
	//char	**sorted;

	// sorted = ft_order_tab(data->secret_envp);
	// if (!sorted)
	// 	return(0);
	i = 0;
	while (data->secret_envp[i])
		ft_print_one_export(data->secret_envp[i++]);
	//free(sorted);
	return (1);
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

char	**ft_order_tab(char **tab)
{
	char	**tab_sorted;
	int		size;
	int		i;
	char	*smaller;

	size = ft_size_tab(tab);
	if (!tab || !*tab)
		return (NULL);
	tab_sorted = (char **)malloc(sizeof(char *) * (size + 1));
	if (!tab_sorted)
		return (NULL);
	smaller = NULL;
	i = 0;
	while (i < size)
	{
		smaller = ft_found_smaller(tab, smaller);
		tab_sorted[i++] = smaller;
	}
	tab_sorted[i] = NULL;
	return (tab_sorted);
}

char	*ft_found_smaller(char **tab, char *smaller)
{
	int		i;
	char	*smallest;

	i = 0;
	smallest = NULL;
	while (tab[i])
	{
		//ft_printf("%s - %s - %s\n", tab[i], smaller, smallest);
		if (!ft_is_before(tab[i], smaller))
		{
			i++;
			continue ;
		}
		if (ft_is_before(tab[i], smallest))
			smallest = tab[i];
		i++;
	}
	return (smallest);
}

/*
	Si c'est negatif, s1 est avant s2
	Si c'est positif, s2 est avant s1
*/
int	ft_is_before(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	if (!s2)
		return (1);
	while (s1[i] && s2[i])
	{
		if (s1[i] < s2[i])
			return (1);
		i++;
	}
	if (s1[i] && s2[i])
		return (0);
	if (!s1[i])
		return (1);
	if (!s2[i])
		return (0);
	return (0);
}