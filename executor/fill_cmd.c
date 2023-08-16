//Ce fichier sera a supprimé a la fin, il permet juste d'avoir des valeurs par défauts de commandes sans passer par le parsing

#include "../minishell.h"

void	ft_fill_simple_cmd1(t_simple_cmd *simple_cmd)
{
	char *cmd;
	char *arg;

	cmd = malloc(sizeof(char) * 3);
	cmd[0] = 'l';
	cmd[1] = 's';
	cmd[2] = '\0';
	
	arg = malloc(sizeof(char) * 3);
	arg[0] = '-';
	arg[1] = 'l';
	arg[2] = '\0';
	
	simple_cmd->cmd_args = (char **)malloc(sizeof(char *) * 3);
	simple_cmd->cmd_args[0] = cmd;
	simple_cmd->cmd_args[1] = arg;
	simple_cmd->cmd_args[2] = NULL;

	simple_cmd->builtin = NO_BUILTIN;
	simple_cmd->redirections = NULL;
	simple_cmd->next = NULL;
	simple_cmd->index = 0;
}

void	ft_fill_simple_cmd2(t_simple_cmd *simple_cmd)
{
	char *cmd;
	char *arg;

	cmd = malloc(sizeof(char) * 5);
	cmd[0] = 'h';
	cmd[1] = 'e';
	cmd[2] = 'a';
	cmd[3] = 'd';
	cmd[4] = '\0';
	
	arg = malloc(sizeof(char) * 3);
	arg[0] = '-';
	arg[1] = '5';
	arg[2] = '\0';

	simple_cmd->cmd_args = (char **)malloc(sizeof(char *) * 3);
	simple_cmd->cmd_args[0] = cmd;
	simple_cmd->cmd_args[1] = arg;
	simple_cmd->cmd_args[2] = NULL;

	simple_cmd->builtin = NO_BUILTIN;
	simple_cmd->redirections = NULL;
	simple_cmd->next = NULL;
	simple_cmd->index = 1;
}

void	ft_fill_simple_cmd3(t_simple_cmd *simple_cmd)
{
	char *cmd;

	cmd = malloc(sizeof(char) * 4);
	cmd[0] = 'c';
	cmd[1] = 'a';
	cmd[2] = 't';
	cmd[3] = '\0';
	simple_cmd->cmd_args = (char **)malloc(sizeof(char *) * 2);
	simple_cmd->cmd_args[0] = cmd;
	simple_cmd->cmd_args[1] = NULL;

	simple_cmd->builtin = NO_BUILTIN;
	simple_cmd->redirections = NULL;
	simple_cmd->next = NULL;
	simple_cmd->index = 2;
}

void	ft_fill_simple_cmd4(t_simple_cmd *simple_cmd)
{
	char *cmd;
	char *arg;

	cmd = malloc(sizeof(char) * 5);
	cmd[0] = 'h';
	cmd[1] = 'e';
	cmd[2] = 'a';
	cmd[3] = 'd';
	cmd[4] = '\0';
	
	arg = malloc(sizeof(char) * 3);
	arg[0] = '-';
	arg[1] = '4';
	arg[2] = '\0';

	simple_cmd->cmd_args = (char **)malloc(sizeof(char *) * 3);
	simple_cmd->cmd_args[0] = cmd;
	simple_cmd->cmd_args[1] = arg;
	simple_cmd->cmd_args[2] = NULL;

	simple_cmd->builtin = NO_BUILTIN;
	simple_cmd->redirections = NULL;
	simple_cmd->next = NULL;
	simple_cmd->index = 3;
}

void	ft_fill_simple_cmd5(t_simple_cmd *simple_cmd)
{
	char *cmd;
	char *arg;

	cmd = malloc(sizeof(char) * 5);
	cmd[0] = 'h';
	cmd[1] = 'e';
	cmd[2] = 'a';
	cmd[3] = 'd';
	cmd[4] = '\0';
	
	arg = malloc(sizeof(char) * 3);
	arg[0] = '-';
	arg[1] = '3';
	arg[2] = '\0';

	simple_cmd->cmd_args = (char **)malloc(sizeof(char *) * 3);
	simple_cmd->cmd_args[0] = cmd;
	simple_cmd->cmd_args[1] = arg;
	simple_cmd->cmd_args[2] = NULL;

	simple_cmd->builtin = NO_BUILTIN;
	simple_cmd->redirections = NULL;
	simple_cmd->next = NULL;
	simple_cmd->index = 4;
}
