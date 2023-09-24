/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snaggara <snaggara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 14:14:00 by snaggara          #+#    #+#             */
/*   Updated: 2023/09/24 13:30:50 by snaggara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/wait.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <dirent.h>
# include <signal.h>
# include <sys/stat.h>
# include <termios.h>
# include "libft-plus/libft/libft.h"
# include "libft-plus/printf/ft_printf.h"
# include "libft-plus/get-next-line/get_next_line.h"

# define E_PIPE "error: Pipe error "
# define E_CHILD "error: Fork went wrong "
# define E_CMD_NOT_FOUND "%s: command not found\n"
# define E_SYNTAXE "erreur de syntaxe près du symbole inattendu "
# define TMP_FILE_NAME ".tmp_here_doc_name_"
# define E_CD "cd: %s: Aucun fichier ou dossier de ce type\n"
# define E_CD_ARG "cd: trop d'arguments\n"
# define E_HERE_DOC "Here doc not created properly\n"
# define E_SIG_HEREDOC "warning: here-document at line delimited \
by end-of-file\n"
# define E_EXPORT_NVALID "Erreur : export: '%s' not a valid identifier\n"

/* Un enum de la liste des builtin*/
typedef enum s_builtin
{
	NO_BUILTIN,
	ECHOO,
	CD,
	PWD,
	EXPORT,
	UNSET,
	ENV,
	EXIT
}	t_builtin;

/* Un enum des différents operators*/
typedef enum s_operator
{
	NONE,
	SUP,
	SUPSUP,
	INF,
	INFINF,
	PIPE
}	t_operator;

/* Un enum du type de chaine de caractere d'un operator*/
typedef enum s_str_type
{
	NO_QUOTE,
	SINGLE_QUOTE,
	DOUBLE_QUOTE
}	t_str_type;

typedef struct s_lexer
{
	char			*word;
	t_operator		operator;
	int				index;
	t_str_type		str_type;
	struct s_lexer	*next;
	struct s_lexer	*prev;
}	t_lexer;

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
	char			**secret_envp;
	char			*full_cmd;
	int				exit_status;
	int				nb_cmd;
	t_simple_cmd	*first_cmd;
	pid_t			*child;
	t_lexer			*lexer;
	int				pipe[2][2];
	int				loop;
	char			*input;
	struct termios	terminal;
}	t_data;

/* Executor Part*/
int				executor(t_data *data);
int				ft_fill_path(t_data *data);
void			ft_fill_simple_cmd1(t_simple_cmd *simple_cmd);
void			ft_fill_simple_cmd2(t_simple_cmd *simple_cmd);
void			ft_fill_simple_cmd3(t_simple_cmd *simple_cmd);
void			ft_fill_simple_cmd4(t_simple_cmd *simple_cmd);
void			ft_fill_simple_cmd5(t_simple_cmd *simple_cmd);
void			ft_create_process(t_data *data, t_simple_cmd *browse, int i);
int				ft_malloc_child_pid(t_data *data);
void			ft_wait_children(t_data *data);
int				ft_create_all_process(t_data *data);
void			ft_close_pipe(int *pipe);
void			ft_close_pipes(t_data *data);
int				ft_process_cmd1(t_data *data, t_simple_cmd *cmd);
int				ft_exec_cmd(t_data *data, t_simple_cmd *cmd);
char			*ft_add_slash(char *path);
int				ft_nb_slash_to_add(char *path);
void			ft_child(t_data *data, t_simple_cmd *browse, int i);
void			ft_fill_redirection1(t_lexer *redirection);
int				ft_cmd_valid(t_data *data, t_simple_cmd *cmd);
int				ft_handle_redirection(t_data *data, t_simple_cmd *cmd);
void			ft_fill_redirection2(t_lexer *redirection);
int				ft_test_cmd_and_redirections(t_data *data, t_simple_cmd *cmd);
int				ft_first_child(t_data *data, t_simple_cmd *cmd, int i);
int				ft_middle_child(t_data *data, t_simple_cmd *cmd, int i);
int				ft_last_child(t_data *data, t_simple_cmd *cmd, int i);
int				ft_inf_operator(t_simple_cmd *cmd, t_lexer *redirection);
int				ft_sup_operator(t_simple_cmd *cmd, t_lexer *redirection);
int				ft_redirect_fdin(t_simple_cmd *cmd);
int				ft_redirect_fdout(t_simple_cmd *cmd);
void			ft_close_redir_fds(t_data *data);
void			ft_free_double_tab(char **tab);
void			ft_free_simple_cmd(t_data *data);
void			ft_free_lexer(t_lexer *lexer);
void			ft_free_for_next_command(t_data *data);
void			ft_free_path(t_data *data);
int				ft_sup_sup_operator(t_simple_cmd *cmd, t_lexer *redirection);
int				ft_handle_here_doc(t_simple_cmd *cmd, t_lexer *redirection);
int				ft_handle_here_docs(t_data *data);
int				ft_inf_inf_operator(t_simple_cmd *cmd, t_lexer *redirection);
int				ft_is_same_str(char *str1, char *str2);
void			ft_delete_here_doc_files(t_data *data);
int				ft_exec_one_cmd(t_data *data);
int				ft_child_one_cmd(t_data *data);
void			ft_finish_child(t_data *data, t_simple_cmd *cmd);
int				ft_discriminate_child(t_data *data, t_simple_cmd *cmd, int i);
int				ft_open_here_doc_file(t_simple_cmd *cmd, char *file_name);
char			*ft_create_here_doc_filename(t_simple_cmd *cmd);
void			ft_free_path_before(char **path, int i);
int				ft_exec_without_fork(t_simple_cmd *cmd);
int				ft_exec_one_cmd_builtin(t_data *data);
char			*ft_create_here_doc_filename(t_simple_cmd *cmd);
int				ft_end_handle_here_doc(t_simple_cmd *cmd, t_lexer *redirection,
					char *stdin_line, char *file_name);
int				ft_how_to_exec(t_data *data);
void			ft_init_pipe(t_data *data);
/* Lexer */
int				ft_minishell_loop(t_data *data);
char			*read_input();
int				ft_lexer(t_data *data);
int				ft_is_space(char c);
t_lexer			*ft_delimite(t_lexer *lexer);
int				ft_add_char(t_lexer *current, char c);
t_lexer			*ft_begin_lexer(void);
int				ft_is_beg_ope(char c);
int				ft_is_ope(char c1, char c2);
void			ft_visualise_lexer(t_data *data);
int				ft_quote_not_over(t_data *data, int *i);
int				ft_is_second_part_op(t_data *data, t_lexer **current, int *i);
int				ft_delimite_op(t_data *data, t_lexer **current, int *i);
int				ft_end_double_quote(t_data *data, t_lexer **current, int *i);
int				ft_end_single_quote(t_data *data, t_lexer **current, int *i);
int				ft_start_single_quote(t_data *data, t_lexer **current, int *i);
int				ft_start_double_quote(t_data *data, t_lexer **current, int *i);
int				ft_start_begin_op(t_data *data, t_lexer **current, int *i);
int				ft_space_separator(t_data *data, t_lexer **current, int *i);
int				ft_lexer_in_loop(t_data *data, t_lexer **current, int *i);
void			ft_fill_lexer_ope(t_data *data);
void			ft_detect_operator(t_lexer *current);
int				ft_space_to_ignore(t_data *data, int *i);
void			ft_delete_last_lexer_if_empty(t_lexer *current);
int				ft_lex_ex_parse(t_data *data);
char			*ft_strdup_plus_n(const char *s);
void			ft_clean_lexer(t_lexer *lexer);
/* PARSER */
int				ft_parser(t_data *data);
int				ft_parse_pipe_and_redir(t_data *data);
void			ft_visualise_cmd(t_data *data);
int				ft_delete_redir_lexer(t_data *data, t_lexer **lexer);
void			ft_free_lexer_node(t_lexer **lexer);
int				ft_is_redir(t_operator op);
int				ft_redir_in_simple_cmd(t_lexer *current_lexer,
					t_simple_cmd *current_cmd);
int				ft_add_in_cmd_redir(t_simple_cmd *cmd, t_lexer *lexer);
char			*ft_get_redirection_file_name(t_lexer *current_lexer);
int				ft_syntax_redirection(t_lexer *current_lexer);
void			ft_syntaxe_error(char const c);
t_simple_cmd	*ft_add_one_simple_cmd(t_simple_cmd *current);
t_simple_cmd	*ft_create_one_simple_cmd(void);
int				ft_delete_end_of_lexer(t_lexer **lexer);
void			ft_delete_and_relink(t_lexer **lexer);
int				ft_add_cmd_if_pipe(t_simple_cmd **current_cmd,
					t_lexer *current_lexer);
void			ft_redir_is_first(t_data *data, t_lexer **lexer);
int				ft_is_space_lexer(t_lexer *lexer);
int				ft_parse_cmds_arg(t_data *data);
int				ft_int_arg_tab(t_simple_cmd *cmd, t_lexer *lexer);
int				ft_add_arg_to_cmd(t_simple_cmd *cmd, char *arg);
int				ft_count_args(t_lexer *lexer);
int				ft_parse_pipe_and_redir(t_data *data);
int				ft_count_cmd(t_data *data);
void			ft_fill_built_in(t_data *data);
int				ft_is_same_word(char const *s1, char const *s2);
int				ft_check_valids_cmds(t_data *data);
int				ft_check_valid_cmd(t_simple_cmd *current_cmd);
void			ft_fill_each_built_in(t_simple_cmd *current_cmd);
int				ft_add_to_last_arg(t_simple_cmd *cmd, char *word);
int				ft_add_arg_to_cmd2(int *new_arg, t_simple_cmd *cmd,
					t_lexer *lexer);
int				ft_add_arg_from_lexer(int *new_arg, t_simple_cmd **cmd,
					t_lexer **lexer);
int				ft_char_is_stop_dollar(char c);
char			*ft_join_char(char *str, char c);
int				ft_is_just_dollar_char(t_lexer *lexer, char *str);
/* Builtin */
void			ft_exit(t_data *data);
void			ft_pwd(void);
int				ft_cd(t_data *data);
int				ft_fill_secret_envp(t_data *data);
int				ft_size_tab(char **tab);
int				ft_update_pwd_envp(t_data *data);
int				ft_change_directory(t_data *data, char *dest_file);
char			*ft_create_new_pwd(t_data *data, char *dest_file);
char			*ft_get_pwd_from_envp(char **envp);
int				ft_test_dir(t_data *data, char *path);
int				ft_update_oldpwd_envp(t_data *data);
void			ft_env(t_data *data);
int				ft_export(t_data *data, t_simple_cmd *cmd);
void			ft_print_all_export(t_data *data);
void			ft_print_one_export(char *line);
char			*ft_get_key(char *str);
int				ft_add_one_export(t_data *data, char const *key, char *str);
int				ft_add_to_env(t_data *data, t_simple_cmd *cmd);
int				ft_add_one_envp(t_data *data, char *str);
int				ft_same_key(char *str, char const *key);
int				ft_unset(t_data *data, t_simple_cmd *cmd);
int				ft_update_secret_env_without(t_data *data, int skip);
int				ft_echo(t_data *data, t_simple_cmd *cmd);
t_lexer			*ft_found_begin_echo(t_lexer *lexer);
int				ft_is_flag_n(char *str);
void			ft_visualise_lexer2(t_lexer *lexer);
int				ft_expander(t_data *data);
int				ft_replace_dollar(t_data *data, t_lexer *lexer);
char			*ft_found_replace_value(t_data *data, char *word);
char			*ft_extract_word(char *str);
int				re_doc_file(t_lexer *lexer);
char			**ft_order_tab(char **tab);
char			*ft_found_smaller(char **tab, char *smaller);
int				ft_is_before(const char *s1, const char *s2);
int				ft_test_key_and_print(t_data *data);
int				ft_check_error(t_data *data, t_lexer *lexer);
char			*ft_key_from_arg(t_simple_cmd *cmd, int *i);
int				ft_echo_loop(t_data *data, t_lexer *begin_lexer);
// Signaux
int				ft_signal(void);
void			handler_c(int signum);
int				ft_signal_ignore(void);
void			ft_set_terminal_settings(t_data *data);
int				ft_is_end_of_str(char *str, char *needle);
char			*ft_reverse_str(char *str);
void			handler_slash(int signum);
int				ft_signal_slash(void);
int				ft_signal_slash_ignore(void);
void			ft_restore_terminal(t_data *data);
size_t			ft_strcat(char *dest, const char *src);
int				ft_increment_shell_level(t_data *data);
int				ft_add_old_pwd(t_data *data);
int				ft_add_pwd(t_data *data);
int				ft_exist_in_secret_env(t_data *data, char *key);
extern int		g_global_state;

#endif
