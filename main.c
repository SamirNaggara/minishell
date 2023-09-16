/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snaggara <snaggara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 14:12:32 by snaggara          #+#    #+#             */
/*   Updated: 2023/09/16 15:36:29 by snaggara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_global_state = 0;

/*


Trier export ou env par ordre alpha
shell level eventuellement
env -i bash -> le env contient quand meme quelques elements
sup tous les elements de env

Si tu crees un dossier, que tu rentres dans le dossier, et que tu supprimes
le dossier dans lequel tu es, fais en sorte que ca te ramene dans home pour
pas que ca segfault


export " "
bash: export: ` ': not a valid identifier
(et ca renvoie 1)

export 6=9
bash: export: `6=9': not a valid identifier

export 6=9 7=9
bash: export: `6=9': not a valid identifier
bash: export: `7=9': not a valid identifier

Attention, sur export les chiffres marchent pas, mais certains caracteres passent, genre _
Regarde la doc

T'as oublier de mettre la boucle dans le unset pour supprimer plusieurs elements en meme temps

export ""=9
bash: export: `=9': not a valid identifier

echo $"?"
Doit rendre pareil que sur batch

echo -nnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnn d
Il faut que ca rende comme sur bash, que d
echo -nnnnnnnnnnnnnnnnnnngnnnnnnnnnn d
Mais la ca affiche

Change le msg 'erreur echo a >< d

Dans echo check la valeur de retour lorsque message d'erreur

echo $USER
<< $USER

cat | cat | ls
Dvriat afficher ls, puis appuyer 2 fois sur entrer pour les 2 cats

*/
int	main(int ac, char **av, char **envp)
{
	t_data	data;

	ft_memset(&data, 0, sizeof(data));
	ft_set_terminal_settings(&data);
	ft_signal();
	ft_signal_slash_ignore();
	(void)ac;
	(void)av;
	data.envp = envp;
	ft_fill_secret_envp(&data);
	ft_minishell_loop(&data);
	ft_restore_terminal(&data);
	ft_free_double_tab(data.secret_envp);
	return (data.exit_status);
}
