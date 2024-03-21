/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cviegas <cviegas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 16:46:32 by cviegas           #+#    #+#             */
/*   Updated: 2024/03/21 21:16:29 by cviegas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_symbol(char c)
{
	if (c == '|' || c == '&' || c == '<' || c == '>')
		return (1);
	return (0);
}

bool	is_whitespace(char c)
{
	if (c == ' ' || c == '\t')
		return (1);
	return (0);
}

// ft_strlen For more code visibility
size_t	len(const char *s)
{
	return (ft_strlen(s));
}

int	protected_addback(t_list **lst, char *str)
{
	char	*new_str;
	t_list	*new_nod;

	new_str = ft_strdup(str);
	if (!new_str)
		return (-1);
	new_nod = ft_lstnew(new_str);
	if (!new_nod)
		return (free(new_str), -1);
	ft_lstadd_back(lst, new_nod);
	return (1);
}

/*handles parenthesis priority*/

bool	should_continue(size_t type, size_t ignore_lvl)
{
	return ((type != OR_IF && type != AND_IF) || ignore_lvl > 1);
}
