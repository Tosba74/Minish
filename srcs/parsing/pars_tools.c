/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_tools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmangin <bmangin@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/08 01:43:20 by bmangin           #+#    #+#             */
/*   Updated: 2021/11/09 20:00:06 by bmangin          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minish.h"

int	is_builtin(char *s)
{
	int		i;
	char	*built[10];

	i = -1;
	built[0] = "echo";
	built[1] = "cd";
	built[2] = "pwd";
	built[4] = "export";
	built[5] = "unset";
	built[6] = "env";
	built[7] = "exit";
	built[8] = "history";
	built[9] = NULL;
	while (built[++i])
		if (!ft_strcmp(built[i], s))
			return (i);
	return (-1);
}

char	*find_error(t_token *tok)
{
	t_token	*cpy;

	cpy = tok;
	while (cpy)
	{
		if (cpy->type == ERROR)
			return (ft_strjoin(cpy->value, " :"));
		cpy = cpy->next;
	}
	return (NULL);
}

int	count_this_char(char *s, char c)
{
	int	i;
	int	counter;

	i = 0;
	counter = 0;
	while (s[++i])
		if (s[i] == c)
			counter++;
	return (counter);
}
