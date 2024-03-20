/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: legrandc <legrandc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 15:30:58 by legrandc          #+#    #+#             */
/*   Updated: 2024/03/20 20:00:09 by legrandc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
// # define _XOPEN_SOURCE 600
# include "includes/quoicoulibft/libft.h"
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
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

extern int			g_exit_status;

typedef struct s_tokens
{
	bool			error;
	struct s_tokens	*next;
	size_t			type;
	char			*content;
	size_t			len;
	size_t			start;
	bool			closed;
	bool			is_single_quoted;
	bool			is_double_quoted;
	int				end_heredoc[2];
	struct s_tokens	*last;
}					t_tokens;

typedef struct s_cmd
{
	t_tokens		*token;
	size_t			len;
	char			**args;
	char			*path;
	int				builtin;
}					t_cmd;

typedef struct s_hdc
{
	char			*line;
	char			*new_line;
	size_t			line_nb;
	bool			malloc_crampted;
}					t_hdc;

typedef struct s_vars
{
	size_t			ignore_lvl;
	char			*readlinestring;
	int				git_repo_name[2];
	bool			line_was_expanded;
	t_list			*history;
	t_list			*last_command;
	bool			command_was_built_in;
	t_list			*env_list;
	char			*line;
	size_t			index;
	size_t			close_index;
	char			**env_path;
	char			**env;
	t_tokens		*tokens;
	t_cmd			cmd;
	int				fildes[2];
	int				last_fd;
	int				last_pid;
	size_t			pipe_nb;
	size_t			cmd_i;
	int				infile_fd;
	int				outfile_fd;
	bool			in_dquote;
	bool			in_quote;
	bool			in_expanded_var;
	size_t			end_of_var;
	void			(*function)(char **, struct s_vars *);
	int				old_stdout;
	int				old_stdin;
	t_hdc			hdc;
	bool			is_child;
	bool			dash_c;
}					t_vars;

typedef enum e_type
{
	WORD,
	PIPE,
	AND_IF,
	OR_IF,
	LESS,
	GREAT,
	DLESS,
	DGREAT,
	FILE_IN,
	FILE_OUT,
	HEREDOC_DELIM,
	DFILE_OUT,
	PARENTHESES_IN,
	PARENTHESES_OUT,
}					t_type;

/* PARSING */
t_list				*create_env_list(char **env, bool *malloc_crampt);
int					parsing(t_vars *vars);
void				init_vars(t_vars *v);
int					get_type_and_len(t_vars *vars);
bool				is_syntax_correct(char *line, t_vars *v);
int					there_is_a_quote(t_vars *v);
int					there_is_a_dquote(t_vars *v);
int					not_in_quote(t_vars *v);
bool				needs_to_be_expanded(t_vars *v);
int					expand_this_shit(t_vars *v);
int					var_is_exit_status(t_vars *v);
int					replace_var_name_by_value(t_vars *v, char *var_value,
						size_t var_name_len);

/*		TOKENS UTILS */
t_tokens			*tok_new(char *content, size_t type);
t_tokens			*tok_new_quoted(char *content, size_t type, bool s_quote,
						bool d_quote);
void				tok_addback(t_tokens **tokens, t_vars *vars, t_tokens *new);
void				tok_clear(t_tokens **tokens);
void				tok_print(t_tokens *tokens);
bool				tok_close_and_addback(t_tokens **tokens, t_vars *vars,
						int type);
bool				tok_addback_and_close(t_tokens **tokens, t_vars *vars,
						int type);

/*		PARSING UTILS */
bool				is_whitespace(char c);
bool				is_symbol(char c);
bool				is_tok_symbol(t_tokens token);
size_t				len(const char *s);
int					expand_this_shit(t_vars *v);

/*		UTILS */
void				clean_vars(t_vars *vars);
void				berr(char *token, t_vars *v);
void				eof_err(char *match, t_vars *v);
void				s(void);
int					protected_addback(t_list **lst, char *str);

/* HEREDOC */
int					exec_heredoc(t_tokens *tok, t_vars *v);
void				hderr(size_t line_nb, char *limiter);

/* GNL*/
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 4000
# endif

/* COLOR CODES */
# define BLUE "\033[0;34m"
# define PINK "\033[0;35m"
# define BOLD "\033[1m"
# define RESET "\033[0m"

/* FUNCTIONS */
void				p_free(void *p);
void				update_rl_name(t_vars *v);
void				ft_close(int *fd);
int					parse_tokens(t_tokens *tok);
int					tok_add_inbetween(t_tokens **first, t_tokens **new);
int					turn_env_into_char(t_vars *v);

int					expand_this_shit_hd(char **new_line, size_t *index,
						t_vars *v);
void				hderr(size_t line_nb, char *limiter);
bool				is_there_delimiter(char *line, char *limiter,
						size_t limiter_len);
int					var_is_exit_status_hd(char **new_line, size_t *i);
int					replace_var_name_by_value_hd(size_t *i, char **line,
						char *value, size_t var_name_len);
char				*whats_the_var(char *line, size_t index);
bool				is_snakecase_or_qmark(char c);
int					expand_line(char *line, char **new_line, t_vars *v);

bool				there_is_this_char(char *line, char c);
void				err_squid(const char *s, bool print_strerrno);
void				change_ignore_lvl(size_t *ignore_lvl, size_t type);
bool				should_continue(size_t type, size_t ignore_lvl);
int					what_token_type_is_it(t_vars *vars);
bool				tok_close_and_addback(t_tokens **tokens, t_vars *vars,
						int type);
int					case_and(t_vars *vars);
int					maybe_add_to_env(char *line, t_vars *v);
char				*ft_getcwd(void);
int					replace_the_var(t_list **env, char *line);
char				*search_var_in_env(t_vars *v, char *var_to_find,
						bool *malloc_crampt);
char				*search_var_in_env(t_vars *v, char *var_to_find,
						bool *malloc_crampt);
bool				var_is_already_in_env(char *line, t_list *env);
void				set_signals_cmd(t_vars *vars);
void				set_signals(t_vars *vars);
void				get_fds(t_vars *vars);
void				search_and_execve(t_vars *vars);
int					is_builtin(t_vars *vars);
void				init_minishell(t_vars *vars, char **env);
void				append_to_history(t_vars *vars);
char				*gnl_no_nl(int fd);
int					save_line(t_vars *vars);
void				get_history(t_vars *vars);
int					dup2_and_close(int *fd1, int fd2);
int					redirect(t_vars *vars);
int					case_parenthese(t_vars *vars, int type);
int					case_and(t_vars *vars);
int					case_pipe(t_vars *vars);
int					case_less(t_vars *vars);
int					case_great(t_vars *vars);
int					case_word(t_vars *vars);
int					tok_close(t_vars *vars);
int					get_cmd_infos(t_tokens **curr, t_vars *vars);
int					get_path(char *command, t_vars *vars);
int					wait_commands(t_vars *vars);
void				syntax_error(t_tokens *tokens);
int					is_metachar(t_tokens token);
void				get_paths(t_vars *vars);
void				free_matrix(char **t);
int					is_builtin(t_vars *vars);
int					exec(t_vars *vars);

/* BUILT INS */
void				ft_echo(char **cmd, t_vars *vars);
void				ft_cd(char **cmd, t_vars *vars);
void				ft_pwd(char **cmd, t_vars *vars);
void				ft_export(char **cmd, t_vars *vars);
void				print_env_export(char **env);
void				print_env_export_list(t_list *env);
void				print_env(t_list *env);
bool				there_is_an_equal(char *line);
void				ft_unset(char **cmd, t_vars *vars);
void				ft_env(char **cmd, t_vars *vars);
void				ft_exit(char **cmd, t_vars *vars);

# define SQUIDYSHELL "\001\033[1;35m\002SquidyShell\001\033[0m\002 "
# define GREENARROW "\001\033[1;32m\002➜\001\033[0m\002 "
# define REDARROW "\001\033[1;31m\002➜\001\033[0m\002 "
# define BBLUE "\033[1;36m"
# define WRITE 1
# define READ 0
# define STDIN STDIN_FILENO
# define STDOUT STDOUT_FILENO
# define STDERR STDERR_FILENO
# define SUCCESS EXIT_SUCCESS
# define FAILURE EXIT_FAILURE

# define SQUID "🦑: "
# define HDERR_0 "warning: here-document at line "
# define HDERR_1 " delimited by end-of-file (wanted `"
# define EOF_ERR "🦑: syntax error: unexpected end of file\n"
# define DIR_ERROR "error retrieving current directory: "
# define GETCWD_ERROR "getcwd: cannot access parent directories:"
# define HISTORY_NAME ".squidyshell_history"

#endif // !MINISHELL_H
