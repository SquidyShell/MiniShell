/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cviegas <cviegas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 15:30:58 by legrandc          #+#    #+#             */
/*   Updated: 2024/03/13 17:32:17 by cviegas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "includes/quoicoulibft/libft.h"
# include <errno.h>
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
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

typedef struct s_vars
{
	t_list			*history;
	t_list			*last_command;
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
	ENV_VAR,
	EXIT_STATUS,
}					t_type;

/* PARSING */
t_list				*create_env_list(char **env);
int					parsing(t_vars *vars);
void				init_vars(t_vars *v);
int					get_type_and_len(t_vars *vars);
bool				is_syntax_correct(char *line);
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

/*		PARSING UTILS */
bool				is_whitespace(char c);
bool				is_symbol(char c);
size_t				len(const char *s);
int					search_for_lenght(t_vars *vars);
int					expand_this_shit(t_vars *v);

/*		UTILS */
void				berr(char *token);
void				eof_err(char *match);
void				s(void);

/* GNL*/
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 4000
# endif

typedef struct s_string
{
	char			*content;
	size_t			len;
	size_t			max_size;
}					t_string;

typedef struct s_dyn_env
{
	char			**env;
	size_t			len;
	size_t			max_size;
}					t_dyn_env;

/* COLOR CODES */
# define BLUE "\033[0;34m"
# define PINK "\033[0;35m"
# define BOLD "\033[1m"
# define RESET "\033[0m"

/* FUNCTIONS */
void				get_fds(t_vars *vars);
void				search_and_execve(t_vars *vars);
int					is_builtin(t_vars *vars);
void				init_minishell(t_vars *vars, char **env);
void				append_to_history(t_vars *vars);
char				*gnl_no_nl(int fd);
int					save_line(t_vars *vars);
void				get_history(void);
int					dup2_and_close(int fd1, int fd2);
int					redirect(t_vars *vars);
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
void				ft_unset(char **cmd, t_vars *vars);
void				ft_env(char **cmd, t_vars *vars);
void				ft_exit(char **cmd, t_vars *vars);

# define SQUIDYSHELL "\033[1;35mSquidyShell\033[0m$ "
# define WRITE 1
# define READ 0
# define STDIN STDIN_FILENO
# define STDOUT STDOUT_FILENO
# define STDERR STDERR_FILENO
# define SUCCESS EXIT_SUCCESS
# define FAILURE EXIT_FAILURE
# define EOF_ERR "🦑: syntax error: unexpected end of file\n"

# define MASTER_STRING                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                          \
	"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"
#endif // !MINISHELL_H
