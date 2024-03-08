/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cviegas <cviegas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 15:30:58 by legrandc          #+#    #+#             */
/*   Updated: 2024/03/08 16:04:37 by cviegas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "includes/quoicoulibft/libft.h"
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct s_tokens
{
	t_tokens	*next;
	char		*content;
}				t_tokens;

typedef struct s_vars
{
	t_tokens	*tokens;
	int			pipe;
}				t_vars;

/* FUNCTIONS */

#endif // !MINISHELL_H
