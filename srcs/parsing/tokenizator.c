/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizator.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmangin <bmangin@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 11:22:31 by bmangin           #+#    #+#             */
/*   Updated: 2021/11/22 21:36:28 by bmangin          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minish.h"

int	egal_tok(t_token **tok, char *input)
{
	(void)input;
	addback_cell_tok(tok,
		new_cell_tok(ft_strdup("="), EGAL));
	return (1);
}

static t_type	get_type(char *input, int *i)
{
	while (input[*i] && input[*i] == input[0])
		(*i)++;
	if (*i == 1)
	{
		if (input[0] == '<')
			return (REDIR_L);
		else
			return (REDIR_R);
	}
	else if (*i == 2)
	{
		if (input[0] == '<')
			return (REDIR_LD);
		else
			return (REDIR_RD);
	}
	return (ERROR);
}

static char	*get_redir_value(char *input, int *i, t_type *type)
{
	char	*tmp;

	if (input[*i] == '$')
		(*i)++;
	while (input[*i] && is_spec_char(input[*i]) == -1)
		(*i)++;
	tmp = ft_substr(input, 0, (*i));
	if (!tmp[0])
	{
		tmp = ft_strdup("newline");
		*type = ERROR;
	}
	return (tmp);
}

int	redir_tok(t_token **tok, char *input)

{
	int		i;
	int		j;
	char	*tmp;
	t_type	type;

	i = 0;
	j = 0;
	type = get_type(input, &i);
	while (input[i + j] && input[i + j] == ' ')
		j++;
	if (type == ERROR)
		tmp = ft_substr(input, i - 1, 1);
	else
	{
		j += i;
		i = 0;
		tmp = get_redir_value(input + j, &i, &type);
	}
	addback_cell_tok(tok, new_cell_tok(ft_strdup(tmp), type));
	return (i + j);
}
