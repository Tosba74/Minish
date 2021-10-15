/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmangin <bmangin@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/08 02:00:38 by bmangin           #+#    #+#             */
/*   Updated: 2021/10/14 13:04:21 by bmangin          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minish.h"

int	pipe_tok(t_global *g, char *input)
{
	(void)g;
	(void)input;
	return (1);
}

int	redir_tok(t_global *g, char *input)
{
	(void)g;
	(void)input;
	return (1);
}

void	create_token_envname(char *input, int len)
{
	int	i;

	i = 0;
	while (++i < len)
		printf("\033[32m%c\033[0m", input[i]);
}

void	create_token_envalue(char *input, int len)
{
	int	i;

	i = 0;
	while (++i < len)
		printf("\033[32m%c\033[0m", input[i]);
}

int	add_tok_var(t_global *g, char *input)
{
	int		i;

	i = 1;
	input++;
	if (input[i] == '\0')
	{
		ft_putchar('$');
		return (i);
	}
	if (input[i] == '?')
	{
		printf("comment jreturn l'ancien process?\n");
		i++;
		return (2);
	}
	while (ft_isdefine(input[i]))
		i++;
	(void)g;
	return (0);
}

int	tok_cote(t_global *g, char *input)
{
	int		i;
	char	c;

	i = 0;
	c = input[0];
	input++;
	while (input[++i])
	{
		if (input[i] == c)
		{
			addback_cell_tok(&g->tok,
				new_cell_tok(ft_substr(input, 0, i), STR));
			return (i);
		}
	}
	ft_err(g, "Cote: ", 3);
	return (1);
}
