/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snaggara <snaggara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/01 14:54:46 by snaggara          #+#    #+#             */
/*   Updated: 2023/09/01 15:09:17 by snaggara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_pwd(void)
{
	char cwd[1024];

    if (!getcwd(cwd, sizeof(cwd))) {
        perror("Erreur lors de l'obtention du répertoire de travail actuel");
		exit(0) ;
	}
	printf("Sam : %s\n",cwd);
	exit(0);
}