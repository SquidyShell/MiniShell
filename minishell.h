/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: legrandc <legrandc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 15:30:58 by legrandc          #+#    #+#             */
/*   Updated: 2024/03/08 15:37:15 by legrandc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct s_vars
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
