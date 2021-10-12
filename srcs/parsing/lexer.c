/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmangin <bmangin@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/08 02:00:38 by bmangin           #+#    #+#             */
/*   Updated: 2021/10/12 14:01:55 by bmangin          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minish.h"

void	create_token(char *input, int len)
{
	int		i;
	char	*tmp;

	i = -1;
	tmp = wrmalloc(sizeof(char) * (len - 1));
	input++;
	while (++i < len - 1)
		tmp[i] = input[i];
	tmp[i] = 0;
	printf("\033[32m|%s|\033[0m", tmp);
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

int	add_var_env(t_global *g, char *input)
{
	(void)g;
	// int		i;
	char	c;
	// char 	name;

	// i = 0;
	c = input[0];
	// while (ft_iscapital(input[i]))
	// {
		// return (i);
	// }
	// }
	dprintf(2, "\nAAAAAaaaaahhhHHHH\n");
	return (0);
}

int	token_cote(t_global *g, char *input)
{
	(void)g;
	int		i;
	char	c;

	i = 0;
	c = input[0];
	while (input[++i])
	{
		if (input[i] == c)
		{
			create_token(input, i);	
			return (i);
		}
	}
	ft_err(g, "Cote: ", 3);
	return (0);
}

void	lexer(t_global *g)
{
	char	*input;
	int		i;

	input = get_last_input(g);
	i = -1;
	while (input[++i])
	{
		if (is_spec_char(input[i]) == -1)
			ft_putchar(input[i]);
		else
		{
			if (is_spec_char(input[i]) == 0)
				i += add_var_env(g, input + i);
			else if (is_spec_char(input[i]) == 1 || is_spec_char(input[i]) == 2)
				i += token_cote(g, input + i);
		}
	}
	ft_putchar('\n');
}

