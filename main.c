/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snaggara <snaggara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 14:12:32 by snaggara          #+#    #+#             */
/*   Updated: 2023/09/08 17:35:11 by snaggara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*C'est mooooooooooooooooooche*/
int	main(int ac, char **av, char **envp)
{
	t_data	data;
	
	(void)ac;
	(void)av;
	data.envp = envp;
	data.exit_status = 0;
	ft_fill_secret_envp(&data);
	
	ft_minishell_loop(&data);

	return (data.exit_status);
	
}

/*
	Cree une copie de la variable d'environnement du début
*/
int	ft_fill_secret_envp(t_data *data)
{
	int	i;
	int	size;

	size = ft_size_tab(data->envp);
	i = 0;
	data->secret_envp = (char **)malloc(sizeof(char *) * (size + 1));
	if (!data->secret_envp)
		return (0);
	while (data->envp[i])
	{
		data->secret_envp[i] = ft_strdup(data->envp[i]);
		if (!data->secret_envp[i])
			return (0);
		i++;
	}
	data->secret_envp[i] = NULL;
	return (1);
}
/*
	Calcul la taille d'un tableau qui finit par null
*/
int	ft_size_tab(char **tab)
{
	int	i;

	i = 0;
	while(tab[i])
		i++;
	return (i);
}


//On utilise la fonction getcwd pour obtenir le chemin absolu du répertoire de travail actuel 
char	*read_input(void)
{
	char	*ret;
	char	cwd[256];

	getcwd(cwd, sizeof(cwd));
	ft_strlcat(cwd, " : ", 256);
	ret = readline(cwd);
	return (ret);
}


void	ft_minishell_loop(t_data *data)
{
	char *user_input;

	while (1)
	{
		data->input = read_input();
		if (!data->input)
			break ;
		if (!*data->input)
			continue ;

		user_input = strdup(data->input); 

		if (!ft_lexer(data))
		{
			free(data->input);
			free(user_input); 
			continue ;
		}
		//ft_visualise_lexer(data);
		if (!ft_expander(data))
		{
			free(data->input);
			continue;
		}
		//ft_visualise_lexer(data);

		if (strcmp(data->input, user_input))
		{
			strcat(user_input, "\n");
			strcat(user_input, data->input);
		}
		add_history(user_input);
		free(user_input); 
		if (!ft_parser(data))
		{
			free(data->input);
			continue ;
		}
		//ft_visualise_cmd(data);
		ft_fill_path(data);
		data->child = NULL;
		rl_redisplay();
		executor(data);
		free(data->input);
	}
}


// int	main(int ac, char **av, char **envp)
// {
// 	t_data			data;

// 	(void)ac;
// 	(void)av;

// 	ft_fill_path(&data);
// 	data.envp = envp;
// 	executor(&data);
// 	return (0);
// }

/*
	Samir, il faut que tu remplaces le getenv de Path
	Par ce qui te parmer de shopper l'info dans le
	secretenv
	Sinon, c'est tres bien de le reconstuire a chaque fois finalement
	Puis que le secret env peut etre mis a jour
	Apres, il faut
		-regler le probleme du exit qui ne marche pas tjr
		-Le exis status, voir comment l'adapter pour les builtins
*/
int	ft_fill_path(t_data *data)
{
	char	*tmp_path;

	tmp_path = ft_add_slash(ft_found_replace_value(data, "PATH"));
	if (!tmp_path)
		return (0);
	data->paths = ft_split(tmp_path, ':');
	if (!data->paths)
		return (free(tmp_path), 0);
	free(tmp_path);
	return (1);
}
