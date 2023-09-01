/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snaggara <snaggara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 14:14:00 by snaggara          #+#    #+#             */
/*   Updated: 2023/09/01 14:03:45 by snaggara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __MINISHELL__
#define __MINISHELL__

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "libft-plus/libft/libft.h"
#include "libft-plus/printf/ft_printf.h"
#include "libft-plus/get-next-line/get_next_line.h"

#define E_PIPE "error: Pipe error "
#define E_CHILD "error: Fork went wrong "
#define E_CMD_NOT_FOUND "command not found: "
#define E_SYNTAXE "erreur de syntaxe près du symbole inattendu "
#define TMP_FILE_NAME ".tmp_here_doc_name_"



/* Un enum de la liste des builtin*/
typedef enum
{
	NO_BUILTIN,
	ECHO,
	CD,
	PWD,
	EXPORT,
	UNSET,
	ENV,
	EXIT
} t_builtin;

/* Un enum des différents operators*/
typedef enum
{
	NONE,
	SUP,
	SUPSUP,
	INF,
	INFINF,
	PIPE
} t_operator;

/* Un enum du type de chaine de caractere d'un operator*/
typedef enum
{
	NO_QUOTE,
	SINGLE_QUOTE,
	DOUBLE_QUOTE
} t_str_type;

typedef struct s_lexer
{
	char 			*word;
	t_operator			operator;
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
	t_lexer				*lexer;
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
	t_lexer			*lexer;
	int				pipe[2][2];
	int				loop;
	char			*input;
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
int		ft_nb_slash_to_add(char *path);
void	ft_child(t_data *data, t_simple_cmd *browse, int i);
void	ft_fill_redirection1(t_lexer *redirection);
int		ft_cmd_valid(t_data *data, t_simple_cmd *cmd);
int		ft_handle_redirection(t_data *data, t_simple_cmd *cmd);
void	ft_fill_redirection2(t_lexer *redirection);
int		ft_test_cmd_and_redirections(t_data *data, t_simple_cmd *cmd);
int		ft_first_child(t_data *data, t_simple_cmd *cmd, int i);
int		ft_middle_child(t_data *data, t_simple_cmd *cmd, int i);
int		ft_last_child(t_data *data, t_simple_cmd *cmd, int i);
int		ft_inf_operator(t_simple_cmd *cmd, t_lexer *redirection);
int		ft_sup_operator(t_simple_cmd *cmd, t_lexer *redirection);
int		ft_redirect_fdin(t_simple_cmd *cmd);
int		ft_redirect_fdout(t_simple_cmd *cmd);
void	ft_close_redir_fds(t_data *data);
void	ft_free_double_tab(char **tab);
void	ft_free_simple_cmd(t_data *data);
void	ft_free_lexer(t_lexer *lexer);
void	ft_free_for_next_command(t_data *data);
void	ft_free_path(t_data *data);
int		ft_sup_sup_operator(t_simple_cmd *cmd, t_lexer *redirection);
int		ft_handle_here_doc(t_simple_cmd *cmd, t_lexer *redirection);
int		ft_handle_here_docs(t_data *data);
int		ft_inf_inf_operator(t_simple_cmd *cmd, t_lexer *redirection);
int		ft_is_same_str(char *str1, char *str2);
void	ft_delete_here_doc_files(t_data *data);
int		ft_exec_one_cmd(t_data *data);
int		ft_child_one_cmd(t_data *data);
void	ft_finish_child(t_data *data, t_simple_cmd *cmd);
int		ft_discriminate_child(t_data *data, t_simple_cmd *cmd, int i);
int		ft_open_here_doc_file(t_simple_cmd *cmd, char *file_name);
char	*ft_create_here_doc_filename(t_simple_cmd *cmd);
void	ft_free_path_before(char **path, int i);
int		ft_exec_without_fork(t_simple_cmd *cmd);
int		ft_exec_one_cmd_builtin(t_data *data);

/* Lexer */
void	ft_minishell_loop(t_data *data);
int	ft_lexer(t_data *data);
int	ft_is_space(char c);
t_lexer	*ft_delimite(t_lexer *lexer);
int	ft_add_char(t_lexer *current, char c);
t_lexer	*ft_begin_lexer(void);
int	ft_is_beg_ope(char c);
int	ft_is_ope(char c1, char c2);
void	ft_visualise_lexer(t_data *data);
int	ft_quote_not_over(t_data *data,  int *i);
int	ft_is_second_part_op(t_data *data, t_lexer **current, int *i);
int	ft_delimite_op(t_data *data, t_lexer **current, int *i);
int	ft_end_double_quote(t_data *data, t_lexer **current, int *i);
int	ft_end_single_quote(t_data *data, t_lexer **current, int *i);
int	ft_start_single_quote(t_data *data, t_lexer **current, int *i);
int	ft_start_double_quote(t_data *data, t_lexer **current, int *i);
int	ft_start_begin_op(t_data *data, t_lexer **current, int *i);
int	ft_space_separator(t_data *data, t_lexer **current, int *i);
int	ft_lexer_in_loop(t_data *data, t_lexer **current, int *i);
void	ft_fill_lexer_ope(t_data *data);
void	ft_detect_operator(t_lexer *current);
int	ft_space_to_ignore(t_data *data, int *i);
void	ft_delete_last_lexer_if_empty(t_lexer *current);

/* PARSER */
int	ft_parser(t_data *data);
int	ft_parse_pipe_and_redir(t_data *data);
void	ft_visualise_cmd(t_data *data);
int	ft_delete_redir_lexer(t_data *data, t_lexer **lexer);
void	ft_free_lexer_node(t_lexer **lexer);
int	ft_is_redir(t_operator op);
int	ft_redir_in_simple_cmd(t_lexer *current_lexer, t_simple_cmd *current_cmd);
int	ft_add_in_cmd_redir(t_simple_cmd *cmd, t_lexer *lexer);
char	*ft_get_redirection_file_name(t_lexer *current_lexer);
int	ft_syntax_redirection(t_lexer *current_lexer);
void	ft_syntaxe_error(char const c);
t_simple_cmd	*ft_add_one_simple_cmd(t_simple_cmd	*current);
t_simple_cmd	*ft_create_one_simple_cmd();
int	ft_delete_end_of_lexer(t_lexer **lexer);
void	ft_delete_and_relink(t_lexer **lexer);
int	ft_add_cmd_if_pipe(t_simple_cmd **current_cmd, t_lexer *current_lexer);
void	ft_redir_is_first(t_data *data, t_lexer **lexer);
int	ft_is_space_lexer(t_lexer *lexer);
int	ft_parse_cmds_arg(t_data *data);
int	ft_int_arg_tab(t_simple_cmd *cmd, t_lexer *lexer);
int	ft_add_arg_to_cmd(t_simple_cmd *cmd, char *arg);
int	ft_count_args(t_lexer *lexer);
int	ft_parse_pipe_and_redir(t_data *data);
int	ft_count_cmd(t_data *data);
void	ft_fill_built_in(t_data *data);
int	ft_is_same_word(char const *s1, char const *s2);
int	ft_check_valids_cmds(t_data *data);
int	ft_check_valid_cmd(t_simple_cmd *current_cmd);


/* Builtin */
void	ft_exit();
#endif