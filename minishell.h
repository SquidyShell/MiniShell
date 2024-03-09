/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cviegas <cviegas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 15:30:58 by legrandc          #+#    #+#             */
/*   Updated: 2024/03/09 11:02:37 by cviegas          ###   ########.fr       */
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
	int				pipe;
}					t_vars;

typedef enum e_type
{
	WORD = 0,
	PIPE = 1,
	AND_IF = 2,
	OR_IF = 3,
	LESS = 4,
	GREAT = 5,
	DLESS = 6,
	DGREAT = 7,
	FILE_IN = 8,
	FILE_OUT = 9,
	HEREDOC_DELIM = 10,
	ENV_VAR = 11,
	EXIT_STATUS = 12,
}					t_type;

/* PARSING */
void				parsing(t_tokens **tokens, char *line);

/*		TOKENS UTILS */
t_tokens			*tok_new(char *content, size_t type);
void				tok_addback(t_tokens **tokens, t_tokens *new);
void				tok_clear(t_tokens **tokens);
void				tok_print(t_tokens *tokens);

/* COLOR CODES */
# define BLUE "\033[0;34m"
# define PINK "\033[0;35m"
# define BOLD "\033[1m"
# define RESET "\033[0m"

#endif // !MINISHELL_H
