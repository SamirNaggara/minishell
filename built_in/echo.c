/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snaggara <snaggara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 14:44:20 by snaggara          #+#    #+#             */
/*   Updated: 2023/09/23 22:15:43 by snaggara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_echo(t_data *data, t_simple_cmd *cmd)
{
	t_lexer	*begin_lexer;

	if (!cmd->cmd_args[1])
	{
		write(1, "\n", 1);
		return (data->exit_status = 0, 1);
	}
	begin_lexer = ft_found_begin_echo(cmd->lexer);
	if (!begin_lexer)
		return (data->exit_status = 1, 0);;
	while (begin_lexer && begin_lexer->operator != PIPE)
	{
		if (!begin_lexer->word)
		{
			begin_lexer = begin_lexer->next;
			continue ;
		}
		if (ft_is_space_lexer(begin_lexer) && begin_lexer->next
			&& (begin_lexer->next->operator == PIPE))
			break ;
		
		write(1, begin_lexer->word, ft_strlen(begin_lexer->word));
		begin_lexer = begin_lexer->next;
	}
	if (!ft_is_flag_n(cmd->cmd_args[1]))
		write(1, "\n", 1);
	return (data->exit_status = 0, 1);
}

/*
	Permet seulement de visualiser un lexer en fonction du lexer
	Juste a des fins de deboggage
*/
void	ft_visualise_lexer2(t_lexer *lexer)
{
	printf("\nLe lexer : \n");
	while (lexer && lexer->word)
	{
		printf("L'element %d : %s\n", lexer->index, lexer->word);
		if (lexer->operator != NONE)
			printf("Operator : %d\n", lexer->operator);
		lexer = lexer->next;
	}
}

/*
	Trouve le lexer qui definit le debut du echo
	Genre on avance de 2 pour ne pas tenir compte
	du echo et du " "
	Puis si c'est un "-n" on l'ignore
*/
t_lexer	*ft_found_begin_echo(t_lexer *lexer)
{
	lexer = lexer->next->next;
	if (ft_is_flag_n(lexer->word))
		lexer = lexer->next;
	if (ft_is_space_lexer(lexer))
		lexer = lexer->next;
	return (lexer);
}

/*
	Verifie que le flag est "-n" exactement
*/
int	ft_is_flag_n(char *str)
{
	int	i;

	i = 1;
	if (!str)
		return (0);
	if (!str[0] || !str[1])
		return (0);
	if (str[0] == '-')
	{
		while (str[i] == 'n')
			i++;
		if (!str[i])
			return (1);
		else
			return (0);
	}
	return (0);
}
