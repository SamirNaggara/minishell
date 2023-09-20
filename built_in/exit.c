/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgoigoux <sgoigoux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/01 14:10:12 by snaggara          #+#    #+#             */
/*   Updated: 2023/09/19 22:10:49 by sgoigoux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
    C'est la fonction appele lorsque l'utilisateur rentre la commande exit
    Attention, la commande doit tout free, ce qui n'est pas le cas la
*/

int	ft_any_number(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] >= '0' && str[i] <= '9')
			return (1);
		i++;
	}
	return (0);
}

void	ft_exit(t_data *data)
{
	t_lexer	*lexer;

	lexer = data->lexer;
	//NE PAS OUBLIER LES MESSAGES D'ERREURS
	while (lexer && lexer->word && lexer->next != NULL)
	{
		lexer = lexer->next;
		if (lexer->next == NULL)
		{
			if (ft_any_number(lexer->word))
				data->exit_status = ft_atoi(lexer->word);
			else if (lexer->index >= 4)
				data->exit_status = 1;
			else
				data->exit_status = 2;
			// Le if qui suit est à revoir 
			if ((ft_strncmp(lexer->prev->word, " ", \
			ft_strlen(lexer->prev->word))))
			{
				if (lexer->prev->word[0] == '-')
					data->exit_status += 56;
			}
		}
	}
	ft_clean_lexer(data->lexer);
	ft_free_simple_cmd(data);
	if (data->secret_envp)
		ft_free_double_tab(data->secret_envp);
	if (data->paths)
		ft_free_double_tab(data->paths);
	free(data->input);
	ft_restore_terminal(data);
	exit(data->exit_status);
}

void	ft_clean_lexer(t_lexer *lexer)
{
	t_lexer	*tmp;

	tmp = lexer;
	while (lexer)
	{
		free(lexer->word);
		lexer = lexer->next;
		free(tmp);
		tmp = lexer;
	}
}
