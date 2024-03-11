/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cviegas <cviegas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 15:30:58 by legrandc          #+#    #+#             */
/*   Updated: 2024/03/11 17:22:38 by cviegas          ###   ########.fr       */
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
}					t_tokens;

typedef struct s_cmd
{
	size_t			len;
	char			**args;
	t_tokens		*infiles;
	t_tokens		*outfiles;
	char			*path;
	int				builtin;
}					t_cmd;

typedef struct s_vars
{
	char			*line;
	size_t			index;
	size_t			close_index;
	char			**env_path;
	char			**env;
	t_tokens		*tokens;
	t_tokens		*last_token;
	t_cmd			cmd;
	int				fildes[2];
	int				last_pid;
	size_t			pipe_nb;
	bool			in_quote;
	bool			in_dquote;
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
	ENV_VAR,
	EXIT_STATUS,
}					t_type;

/* PARSING */
int					parsing(t_vars *vars);
int					get_type_and_len(t_vars *vars);
bool				is_syntax_correct(char *line);
int					not_in_quote(t_vars *v);

/*		TOKENS UTILS */
t_tokens			*tok_new(char *content, size_t type);
t_tokens			*tok_new_quoted(char *content, size_t type, bool s_quote,
						bool d_quote);
t_tokens			*tok_new_closed(char *content, size_t type);
void				tok_addback(t_vars *vars, t_tokens *new);
void				tok_clear(t_tokens **tokens);
void				tok_print(t_tokens *tokens);

/*		PARSING UTILS */
bool				is_whitespace(char c);
bool				is_symbol(char c);
int					search_for_lenght(t_vars *vars);

/*		UTILS */
void				berr(char *token);
void				eof_err(char *match);
void				s(void);

/* COLOR CODES */
# define BLUE "\033[0;34m"
# define PINK "\033[0;35m"
# define BOLD "\033[1m"
# define RESET "\033[0m"

/* FUNCTIONS */
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
void				ft_echo(char **cmd, t_vars *vars);
void				ft_cd(char **cmd, t_vars *vars);
void				ft_pwd(char **cmd, t_vars *vars);
void				ft_export(char **cmd, t_vars *vars);
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

#endif // !MINISHELL_H
