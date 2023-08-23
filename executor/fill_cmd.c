//Ce fichier sera a supprimé a la fin, il permet juste d'avoir des valeurs par défauts de commandes sans passer par le parsing

#include "../minishell.h"

void	ft_fill_simple_cmd1(t_simple_cmd *simple_cmd)
{
	char *cmd;

	cmd = malloc(sizeof(char) * 4);
	ft_bzero(cmd, 4);
	ft_strlcpy(cmd, "cat", 4);
	

	
	simple_cmd->cmd_args = (char **)malloc(sizeof(char *) * 3);
	simple_cmd->cmd_args[0] = cmd;
	simple_cmd->cmd_args[1] = NULL;

	simple_cmd->builtin = NO_BUILTIN;
	simple_cmd->redirections = NULL;
	simple_cmd->next = NULL;
	simple_cmd->index = 0;
	simple_cmd->fd_in = -1;
	simple_cmd->fd_out = -1;
}

void	ft_fill_simple_cmd2(t_simple_cmd *simple_cmd)
{
	char *cmd;
	char *arg;

	cmd = malloc(sizeof(char) * 5);
	ft_bzero(cmd, 5);
	ft_strlcpy(cmd, "head", 5);

	arg = malloc(sizeof(char) * 3);
	ft_bzero(arg, 3);
	ft_strlcpy(arg, "-5", 3);

	simple_cmd->cmd_args = (char **)malloc(sizeof(char *) * 3);
	simple_cmd->cmd_args[0] = cmd;
	simple_cmd->cmd_args[1] = arg;
	simple_cmd->cmd_args[2] = NULL;

	simple_cmd->builtin = NO_BUILTIN;
	simple_cmd->redirections = NULL;
	simple_cmd->next = NULL;
	simple_cmd->index = 1;
	simple_cmd->fd_in = -1;
	simple_cmd->fd_out = -1;
}

void	ft_fill_simple_cmd3(t_simple_cmd *simple_cmd)
{
	char *cmd;

	cmd = malloc(sizeof(char) * 4);
	ft_bzero(cmd, 4);
	ft_strlcpy(cmd, "cat", 4);

	simple_cmd->cmd_args = (char **)malloc(sizeof(char *) * 2);
	simple_cmd->cmd_args[0] = cmd;
	simple_cmd->cmd_args[1] = NULL;

	simple_cmd->builtin = NO_BUILTIN;
	simple_cmd->redirections = NULL;
	simple_cmd->next = NULL;
	simple_cmd->index = 2;
	simple_cmd->fd_in = -1;
	simple_cmd->fd_out = -1;
}

void	ft_fill_simple_cmd4(t_simple_cmd *simple_cmd)
{
	char *cmd;
	char *arg;

	cmd = malloc(sizeof(char) * 5);
	ft_bzero(cmd, 5);
	ft_strlcpy(cmd, "head", 5);

	
	arg = malloc(sizeof(char) * 3);
	ft_bzero(arg, 3);

	ft_strlcpy(arg, "-4", 3);

	simple_cmd->cmd_args = (char **)malloc(sizeof(char *) * 3);
	simple_cmd->cmd_args[0] = cmd;
	simple_cmd->cmd_args[1] = arg;
	simple_cmd->cmd_args[2] = NULL;

	simple_cmd->builtin = NO_BUILTIN;
	simple_cmd->redirections = NULL;
	simple_cmd->next = NULL;
	simple_cmd->index = 3;
	simple_cmd->fd_in = -1;
	simple_cmd->fd_out = -1;
}

void	ft_fill_simple_cmd5(t_simple_cmd *simple_cmd)
{
	char *cmd;

	cmd = malloc(sizeof(char) * 4);
	ft_bzero(cmd, 4);
	ft_strlcpy(cmd, "cat", 4);



	simple_cmd->cmd_args = (char **)malloc(sizeof(char *) * 3);
	simple_cmd->cmd_args[0] = cmd;
	simple_cmd->cmd_args[1] = NULL;

	simple_cmd->builtin = NO_BUILTIN;
	simple_cmd->redirections = NULL;
	simple_cmd->next = NULL;
	simple_cmd->index = 4;
	simple_cmd->fd_in = -1;
	simple_cmd->fd_out = -1;
}

