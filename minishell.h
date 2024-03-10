/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cviegas <cviegas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 15:30:58 by legrandc          #+#    #+#             */
/*   Updated: 2024/03/10 18:30:58 by cviegas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "includes/quoicoulibft/libft.h"
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct s_tokens
{
	struct s_tokens	*next;
	size_t			type;
	size_t			index;
	char			*content;
}					t_tokens;

typedef struct s_vars
{
	t_tokens		*tokens;
	char			**envp;
	int				fildes[2];
	int				last_pid;
	int				pipe;
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
void				parsing(t_tokens **tokens, char *line);
bool				is_syntax_correct(char *line);

/*		TOKENS UTILS */
t_tokens			*tok_new(char *content, size_t type);
void				tok_addback(t_tokens **tokens, t_tokens *new);
void				tok_clear(t_tokens **tokens);
void				tok_print(t_tokens *tokens);

/*		UTILS */
void				berr(char *token);
void				s(void);

/* COLOR CODES */
# define BLUE "\033[0;34m"
# define PINK "\033[0;35m"
# define BOLD "\033[1m"
# define RESET "\033[0m"
# define SQUIDYSHELL "\033[1;35mSquidyShell\033[0m$ "

#endif // !MINISHELL_H
