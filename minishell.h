/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snaggara <snaggara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 14:14:00 by snaggara          #+#    #+#             */
/*   Updated: 2023/08/23 13:52:07 by snaggara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __MINISHELL__
#define __MINISHELL__

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include "libft-plus/libft/libft.h"
#include "libft-plus/printf/ft_printf.h"
#include "libft-plus/get-next-line/get_next_line.h"

#define E_PIPE "error: Pipe error "
#define E_CHILD "error: Fork went wrong "
#define E_CMD_NOT_FOUND "command not found: "
#define TMP_FILE_NAME ".tmp_here_doc_name_"


/* Un enum de la liste des builtin*/
typedef enum
{
	NO_BUILTIN,
	CD,
	PWD,
	EXPORT,
	UNSET,
	ENV,
	EXIT
} t_builtin;

/* Un enum des différents tokens*/
typedef enum
{
	NONE,
	SUP,
	SUPSUP,
	INF,
	INFINF,
	PIPE
} t_token;

/* Un enum du type de chaine de caractere d'un token*/
typedef enum
{
	NO_QUOTE,
	SINGLE_QUOTE,
	DOUBLE_QUOTE
} t_str_type;

typedef struct s_lexer
{
	char 			*word;
	t_token			token;
	int				index;
	t_str_type		str_type;
	struct s_lexer	*next;
	struct s_lexer	*prev;
} 	t_lexer;

typedef struct s_simple_cmd
{
	char				**cmd_args;
	t_builtin			builtin;
	t_lexer				*redirections;
	int					index;
	int					fd_in;
	int					fd_out;
	struct s_simple_cmd	*next;
}	t_simple_cmd;

typedef struct s_data
{
	char			**paths;
	char			**envp;
	int				nb_cmd;
	t_simple_cmd	*first_cmd;
	pid_t			*child;
	int				pipe[2][2];
} t_data;

/* Executor Part*/
int		executor(t_data *data);
int		ft_fill_data(t_data *data);
void	ft_fill_simple_cmd1(t_simple_cmd *simple_cmd);
void	ft_fill_simple_cmd2(t_simple_cmd *simple_cmd);
void	ft_fill_simple_cmd3(t_simple_cmd *simple_cmd);
void	ft_fill_simple_cmd4(t_simple_cmd *simple_cmd);
void	ft_fill_simple_cmd5(t_simple_cmd *simple_cmd);
void	ft_create_process(t_data *data, t_simple_cmd *browse, int i);
int		ft_malloc_child_pid(t_data *data);
void	ft_wait_children(t_data *data);
int		ft_create_all_process(t_data *data);
void	ft_close_pipe(int *pipe);
void	ft_close_pipes(t_data *data);
int		ft_process_cmd1(t_data *data, t_simple_cmd *cmd);
int		ft_exec_cmd(t_data *data, t_simple_cmd *cmd);
char	*ft_add_slash(char *path);
int	ft_nb_slash_to_add(char *path);
void	ft_child(t_data *data, t_simple_cmd *browse, int i);
void	ft_fill_redirection1(t_lexer *redirection);
int	ft_cmd_valid(t_data *data, t_simple_cmd *cmd);
int	ft_handle_redirection(t_data *data, t_simple_cmd *cmd);
void	ft_fill_redirection2(t_lexer *redirection);
int	ft_test_cmd_and_redirections(t_data *data, t_simple_cmd *cmd);
int	ft_first_child(t_data *data, t_simple_cmd *cmd, int i);
int	ft_middle_child(t_data *data, t_simple_cmd *cmd, int i);
int	ft_last_child(t_data *data, t_simple_cmd *cmd, int i);
int	ft_inf_token(t_simple_cmd *cmd, t_lexer *redirection);
int	ft_sup_token(t_simple_cmd *cmd, t_lexer *redirection);
int	ft_redirect_fdin(t_simple_cmd *cmd);
int	ft_redirect_fdout(t_simple_cmd *cmd);
void	ft_close_redir_fds(t_data *data);
void	ft_free_double_tab(char **tab);
void	ft_free_simple_cmd(t_data *data);
void	ft_free_lexer(t_lexer *lexer);
void	ft_free_for_next_command(t_data *data);
void	ft_free_path(t_data *data);
int	ft_sup_sup_token(t_simple_cmd *cmd, t_lexer *redirection);
int	ft_handle_here_doc(t_simple_cmd *cmd, t_lexer *redirection);
int	ft_inf_inf_token(t_simple_cmd *cmd, t_lexer *redirection);
int	ft_is_same_str(char *str1, char *str2);
void	ft_delete_here_doc_files(t_simple_cmd *cmd);

#endif