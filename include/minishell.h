/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+
	+:+     */
/*   By: hrobin <hrobin@student.42.fr>              +#+  +:+
	+#+        */
/*                                                +#+#+#+#+#+
	+#+           */
/*   Created: 2023/09/29 14:31:03 by hrobin            #+#    #+#             */
/*   Updated: 2023/09/29 14:31:03 by hrobin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "libft.h"
# include <dirent.h>
# include <errno.h>
# include <fcntl.h>
# include <limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

extern int	g_exit_code;

typedef struct s_var
{
	char	*new;
	int		start;
	int		k;
	int		squote;
	int		dquote;

}		t_variables;

typedef enum e_parse_flag
{
	None,
	start,
	RedirectName,
	HereDocEof
}		t_parse_flag;

typedef struct s_node
{
	char			*str;
	struct s_node	*next;
}		t_node;

typedef struct s_redirect
{
	int					src_fd;
	char				*dst_name;
	char				*here_doc_eof;
	int					open_flag;
	int					is_heredoc;
	struct s_redirect	*next;
}		t_redirect;

typedef struct s_cmd
{
	t_redirect		*redirect;
	t_node			*command;
	struct s_cmd	*next;
}		t_cmd;

typedef struct s_type
{
	size_t			i;
	char			c;
	char			*buff;
	int				dquote;
	int				squote;
	t_cmd			*current_cmd;
	t_redirect		*current_redirect;
	t_parse_flag	flag;
}		t_type;

typedef struct s_info
{
	char		*line;
	int			sortie;
	char		**cmd;
	char		pwd[2048];
	char		**my_env;
	char		**export;
	int			fds[2];
	int			j;
	int			status;
	bool		a;
	t_cmd		*commandes;
	int			size;
	t_cmd		*tmp;
}		t_info;

int			my_cd(char **cmd, char **env, char *pwd);
int			my_echo(char **cmd, char **env);
int			myy_env(char **env, char **cmd, int type);
void		put_error_env(char *s1, char *s2, char *s3);
void		handle_export_command(t_info *init);
char		**export_variables(char **cmd, char **env, int size);
int			verify_and_count_new_variables(char **cmd, char **env);
int			my_pwd(char *pwd);
char		**my_unset(char **env, char **cmd);

t_cmd		*has_typo_error(t_cmd *cmds);
void		close_fds(t_info init);
void		cleanup_heredoc_file(t_cmd *cmd);
void		free_double_tab(char ***str);
t_cmd		*free_but_not_least(t_cmd *cmd, t_type *type);
void		free_cmds(t_cmd *cmd);
void		free_wrds(t_node *cmd);
void		free_redir(t_redirect *redir);
void		free_double_strings(char *s1, char *s2);
void		multi_free(char ***a, char ***b);

t_info		init_parsing(t_info start);
t_info		main_parsing(t_info start);

int			is_builtin(char **cmd, char **env, char *pwd, char *path_env);
void		setup_pipeline(int begin, int end, int *strout);
char		**custom_redir(t_redirect *cmd, char **tab);
int			child_process(char **cmd, char **env, char *path_env, int sortie);
char		*convert_to_lower_case(char *str);

void		builtin_main(t_info *start);
void		run_shell_command(t_info *init);
int			launch_command_process(char **cmd, char **env, int out);
char		*find_line_path_env(char **env);

char		**process_command_arguments(char **cmd, char **env, int exit_code);
int			sub_var_in_str(char **tmp, int exit_code, char *place, char *start);
int			does_it_parse(t_cmd **cmd, t_type *type, char *line);
int			does_it_command(t_cmd **cmd, t_type *type);
int			does_it_word(t_type *type);
int			does_it_redirect(t_type *type, char *str);
int			how_to_redir(t_type *type, char *str);
void		start_heredoc(t_cmd *cmds);
void		init_arg(t_info *start, char **env);
t_type		init_type(void);
void		init_struct(t_variables *info);
t_cmd		*check_quotes(char *line);
t_cmd		*typo(t_cmd *cmd);
int			one_squote(char *pos, int len);
int			one_dquote(char *pos, int len);
int			uneven_q(char *pos, int len);
char		**trim_quotes_from_array(char **cmd);

void		signal_boss(void);
void		handle_signal(int sig);

char		**new_env(char **env);
char		*custom_env(char *new_str, char **env);
void		export_display_erreur(char *cmd, int nb);
void		handle_invalid_option(char **cmd);
char		*create_new_variable(char *cmd, char **new_var, int j);
int			create_new_env_variables(char **cmd, char **env, char ***new_var);
int			find_variable_index(char **env, char *var, int place);
void		display_error(char *cmd, int nb);
char		*add_double_quotes(char *env);
char		**sort_by_ascii(char **env);
char		*update_environment_variable(char *cmd, char **env, char *place);
char		**duplicate_environment(char **env);
char		**filter_out_empty_strings(char **cmd);
int			compare_strings(char *s1, char *s2);
t_cmd		*create_command(t_cmd **cmd, t_cmd c);
t_node		*create_word(t_node **cmd, t_node new_word);
int			do_heredoc(t_type *type);
t_redirect	*do_redirect(t_redirect **current, t_redirect fill_new);
char		*find_executable_path(char **cmd, char *path_env);
char		**split_path_env(char *path);
char		*ft_strcat_multiple(char *dest, char *a, char *b, char *c);
int			command_not_found_error(char **cmd, char *path_env);
int			command_execution_error(char **cmd, char *path_env, char *new_cmd);
int			search_char(char c, const char *str);
char		*extract_substring(char const *line, unsigned int begin,
				size_t max_len);
char		*join_str(char *str1, char *str2);
char		**tokenize_arguments(char **tab);
char		**split_string(char *str, char *c);
void		end_of_shell(char *str, t_info *start);
int			double_tab_len(char **str);
char		*do_new_buff(char *old_buff, char c);
int			nb_cmds(t_cmd *cmds);
char		**do_tab(t_node *word);
char		**merge_two_tab(char **dptr1, char **dptr2);
char		**add_str_to_tab(char **tab, char *str);
char		**add_token_to_result(char *str, int start, int i, char **tab);
int			find_path_variable_index(char **env);
void		put_str_on_stdout(char *str, int i);
char		*free_and_return_null(char **str);
char		*free_and_return_str(char **tab, char *str);
int			is_character_in_string(char *str, char c);
char		**export_all(char **env, int size);
char		**process_export(char **cmd, char **env, char **new_var);
char		*update_or_add_var(char **env, char *cmd, int *j, char **new_var);

#endif
