/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snaggara <snaggara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/27 13:48:58 by snaggara          #+#    #+#             */
/*   Updated: 2023/08/28 19:43:57 by snaggara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_parser(t_data *data)
{
	t_lexer			*current_lexer;
	t_simple_cmd	*current_cmd;

	if (!data->lexer)
		return (1);
	data->first_cmd = ft_create_one_simple_cmd();
	if (!data->first_cmd)
		return (0);
	current_cmd = data->first_cmd;
	current_lexer = data->lexer;
	while (current_lexer)
	{
		if (!ft_add_cmd_if_pipe(&current_cmd, current_lexer))
			return (0);
		if (ft_is_redir(current_lexer->operator))
		{
			if (!ft_redir_in_simple_cmd(current_lexer, current_cmd))
				return (0);
			if (ft_delete_redir_lexer(data, &current_lexer) == -1)
				continue ;
		}
		current_lexer = current_lexer->next;
	}
	ft_visualise_cmd(data);
	return (1);
}

/*
	Cette fonction ajoute une simple_cmd a la liste chainée
	Si on rencontre un pipe
*/
int	ft_add_cmd_if_pipe(t_simple_cmd **current_cmd, t_lexer *current_lexer)
{
	if (current_lexer->operator == PIPE)
	{
		*current_cmd = ft_add_one_simple_cmd(*current_cmd);
		if (!*current_cmd)
			return (0);
	}
	return (1);
}

void	ft_visualise_cmd(t_data *data)
{
	t_simple_cmd	*current_cmd;
	t_lexer			*current_redirection;

	current_cmd = data->first_cmd;
	while (current_cmd)
	{
		printf("Voila une simple cmd : %d\n", current_cmd->index);
		current_redirection = current_cmd->redirections;

		while (current_redirection)
		{
			printf("	Redireciton file : %s\n", current_redirection->word);
			current_redirection = current_redirection->next;
		}
		current_cmd = current_cmd->next;
	}
}

/*
	Cette fonction s'occupe de supprimer les parties du lexer
	qu'on a mis dans simple cmd pour les redirections
	En les supprimant, elle s'assure que la chaine lexer reste coherente
	Soit c'est la fin et il suffit de supprimer (delete_end_of_lexer)
	Soit c'est pas la fin, et il faut relié ce qui est avant la redir
	avec ce qui est apres
	Si la redirection est dans le tout premier lexer, c'est un cas a part
	on ne peut pas utiliser de "before" comme les autres
	Donc on renvoie 1, et la boucle au dessus fera un continue
*/
int	ft_delete_redir_lexer(t_data *data, t_lexer **lexer)
{
	if (*lexer == data->lexer)
		return (ft_redir_is_first(data, lexer), -1);
	if (ft_delete_end_of_lexer(lexer))
		return (1);
	ft_delete_and_relink(lexer);
	return (1);
}

void	ft_redir_is_first(t_data *data, t_lexer **lexer)
{
	t_lexer	*new_begin;

	if (!ft_is_space((*lexer)->next->word[0]))
			new_begin = (*lexer)->next->next;
		else
		{
			new_begin = (*lexer)->next->next->next;
			ft_free_lexer_node(&(*lexer)->next->next);
		}
		ft_free_lexer_node(&(*lexer)->next);
		ft_free_lexer_node(lexer);
		if (new_begin && ft_is_space(new_begin->word[0]) && new_begin->next)
		{
			*lexer = new_begin->next;
			free(new_begin);
			new_begin = *lexer;
		}
		*lexer = new_begin;
		data->lexer = new_begin;
}

/*
	S'occupe du cas ou on supprime une redir dans le lexer
	Mais qu'il faut relink avec ce qui est apres
*/
void	ft_delete_and_relink(t_lexer **lexer)
{
	t_lexer	*before;
	t_lexer	*after;
	
	before = (*lexer)->prev;
	if (!ft_is_space((*lexer)->next->word[0]))
		after = (*lexer)->next->next;
	else
	{
		after = (*lexer)->next->next->next;
		ft_free_lexer_node(&((*lexer)->next->next));
	}
	before->next = after;
	after->prev = before;
	ft_free_lexer_node(&((*lexer)->next));
	ft_free_lexer_node(lexer);
	if (after && ft_is_space(after->word[0]))
	{
		before->next = after->next;
		if (after->next)
			after->next->prev = before;
		free(after);
	}
	*lexer = before;
}

/*
	Dans la redirection, si la redirection est la fin du lexer
	on free les derniers blocs
	et on arrete la chaine lexer plus tot
*/
int	ft_delete_end_of_lexer(t_lexer **lexer)
{
	t_lexer	*before;
	
	if (!(*lexer)->next->next)
	{
		(*lexer)->prev->next = NULL;
		before = (*lexer)->prev;
		ft_free_lexer_node(&(*lexer)->next);
		ft_free_lexer_node(&(*lexer));
		*lexer = before;
		return (1);
	}
	if (ft_is_space((*lexer)->next->word[0]) && !(*lexer)->next->next->next)
	{
		(*lexer)->prev->next = NULL;
		before = (*lexer)->prev;
		ft_free_lexer_node(&(*lexer)->next->next);
		ft_free_lexer_node(&(*lexer)->next);
		ft_free_lexer_node(&(*lexer));
		*lexer = before;
		return (1);
	}
	return (0);
}

void	ft_free_lexer_node(t_lexer **lexer)
{
	if ((*lexer)->word)
		free((*lexer)->word);
	free(*lexer);
}

int	ft_is_redir(t_operator op)
{
	if (op >= 1 && op <= 4)
		return (1);
	return (0);
}
/*
	Si on a un operateur de redirection
	Alors on regarde si celui d'apres est valide (pas un operateur)
	Et alors on met dans le lexer en cours le mot de redirection
	Puis on met ce lexer dans la simple_cmd
	Puis on supprime la redirection du lexer
*/

int	ft_redir_in_simple_cmd(t_lexer *current_lexer, t_simple_cmd *current_cmd)
{
	if (current_lexer->operator == NONE || current_lexer->operator == PIPE)
		return (0);
	if (!ft_syntax_redirection(current_lexer))
		return (0);
	ft_add_in_cmd_redir(current_cmd, current_lexer);
	return (1);
}

/*
	Dans la simple cmd, il y a un t_lexer de redirection
	On rajoute notre redirection là, a la fin de la chaine
	Ceci est une copie, la chaine de lexer de base n'est pas impacté
	On note que le mot est le file_name, et l'operateur contient l'info
	de redirection
*/
int	ft_add_in_cmd_redir(t_simple_cmd *cmd, t_lexer *lexer)
{
	t_lexer	*browse;
	t_lexer	*new;

	new = ft_begin_lexer();
	if (!new)
		return (0);
	new->word = ft_get_redirection_file_name(lexer);
	if (!new->word)
		return (0);
	new->operator = lexer->operator;
	new->str_type = lexer->str_type;

	if (!cmd->redirections)
		cmd->redirections = new;
	else
	{
		browse = cmd->redirections;
		while (browse->next)
			browse = browse->next;
		new->index = browse->index + 1;
		new->prev = browse;
		new->next = NULL;
		browse->next = new;
	}
	return (1);
}

/*
	Va chercher le nom du fichier de redirection
*/
char	*ft_get_redirection_file_name(t_lexer *current_lexer)
{
	current_lexer = current_lexer->next;
	if (!ft_is_space((current_lexer->word)[0]))
		return (ft_strdup(current_lexer->word));
	return (ft_strdup(current_lexer->next->word));
}

/*
	IL y a une erreur de syntaxe si
	Le caractere d'apres n'existe pas
	ou s'il existe mais que c'est le caractere d'apres qui n'existe pas
	OU bien si c'est un operateur
*/
int	ft_syntax_redirection(t_lexer *current_lexer)
{
	if (!current_lexer)
		return (ft_syntaxe_error('\n'), 0);
	if (!current_lexer->next)
		return (ft_syntaxe_error('\n'), 0);
	current_lexer = current_lexer->next;
	if (current_lexer->operator != NONE)
		return (ft_syntaxe_error(current_lexer->word[0]), 0);
	if (!ft_is_space((current_lexer->word)[0]))
		return (1);
	return (ft_syntax_redirection(current_lexer));
}

/*
	Affiche les erreurs de syntaxe
	Avec le caractere qui pose probleme
*/
void	ft_syntaxe_error(char const c)
{
	fd_printf(STDERR_FILENO, E_SYNTAXE);
	if (c == '\n')
		fd_printf(STDERR_FILENO, "<< newline >>\n");
	else
		fd_printf(STDERR_FILENO, "<< %c >>\n", c);
}
/*
	Ta mission si tu l'acceptes c'est de creer les structures contenant les commandes simples
	Pour l'instant, l'idée c'est de passer une premiere fois pour creer le bon nombre de commandes
	Puis ensuite de placer les redirections si y'en a, et de les retirer du lexer
	Ensuite de placer les commandes et les arguments
	Puis de reperer les builtins
	Puis voila
*/

t_simple_cmd	*ft_add_one_simple_cmd(t_simple_cmd	*current)
{
	t_simple_cmd	*new;

	new = ft_create_one_simple_cmd();
	if (!new)
		return (NULL);
	new->index = current->index + 1;
	current->next = new;
	return (new);
}

t_simple_cmd	*ft_create_one_simple_cmd()
{
	t_simple_cmd	*new;

	new = (t_simple_cmd *)malloc(sizeof(t_simple_cmd));
	if (!new)
		return (NULL);
	new->cmd_args = NULL;
	new->builtin = NO_BUILTIN;
	new->redirections = NULL;
	new->index = 0;
	new->fd_in = -1;
	new->fd_out = -1;
	new->next = NULL;
	return (new);
}
