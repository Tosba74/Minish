/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmangin <bmangin@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/08 02:00:38 by bmangin           #+#    #+#             */
/*   Updated: 2021/10/11 16:14:07 by bmangin          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minish.h"

// char	**find_double_cote(char *s)
// {
// 	int		i;
// 	int		nb_cote;
// 	char	**teub;

// 	i = -1;
// 	nb_cote = counter_this_char(s, '"');
// 	teub = NULL;
// 	dprintf(2, "\033[32mSearch double cote \033[0m\033[33m| %d finded!\033[0m\n", nb_cote);
// 	if (nb_cote == 0)
// 	{
// 		teub = wrmalloc(sizeof(char *) * 2);
// 		teub[0] = s;
// 		teub[1] = NULL;
// 		return (teub);
// 	}
// 	else if (nb_cote % 2 == 1)
// 		ft_err("BRAINFUCK: ", 2);
// 	else
// 		sub
// 	return (teub);
// }

// char	**find_double_cote(char *s)
// {
// 	int		i;
// 	int		t;
// 	int		y;
// 	int		nb_cote;
// 	char	**teub;

// 	i = 0;
// 	t = 0;
// 	y = 0;
// 	nb_cote = counter_cote(s);
// 	teub = NULL;
// 	if (nb_cote % 2 == 1)
// 		ft_err("Cote unclosed: ", 5);
// 	while (nb_cote != 0)
// 	{
// 		while (s[i])
// 		{
// 			teub[t][y++] = s[i];
// 			if (s[i] == 34)
// 				teub[t++][y] = 0;
// 			i++;
// 		}
// 		teub[t][y] = 0;
// 		nb_cote -= 2;
// 	}
// 	teub [t + 1] = NULL;
// 	return (teub);
// }

// void	dispath_jobs(t_global *g)
// {
// 	int		i;
// 	char	**jobs;

// 	i = 0;
// 	jobs = ft_split(get_last_input(g), '|');
// 	if (jobs)
// 	{
// 		dprintf(STDERR_FILENO, "T'es la ?\n");
// 		while (jobs[i])
// 		{
// 			dprintf(STDERR_FILENO, "teub[%d] = |%s|\n", i, jobs[i]);
// 			addback_cell_pipe(&g->pipe, new_cell_pipe(skip_space(jobs[i])));
// 			i++;
// 		}
// 	}
// }

int	add_var_env(t_global *g, char *input)
{
	(void)g;
	(void)input;
	dprintf(2, "\nOOOOOooooohhhHHHH\n");
	return (0);
}

int	token_cote(t_global *g, char *input)
{
	(void)g;
	(void)input;
	// int		i;
	// char	c;

	// i = 0;
	// c = input[0];
	// while (input[++i])
	// {
	// 	if (input[i] == c)
					
	// }
	dprintf(2, "\nAAAAAaaaaahhhHHHH\n");
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
		if (is_spec_char(input[i]) == 0)
			i += add_var_env(g, input + i);
		else if (is_spec_char(input[i]) == 1 || is_spec_char(input[i]) == 2)
			i += token_cote(g, input + i);
		else
			ft_putchar(input[i]);
	}
}

void	parser(t_global *g)
{
	int		i;
	char	**tmp;

	i = -1;
	tmp = NULL;
	// tmp = find_double_cote(g->pipe->pipe_line);
	lexer(g);
	// dispath_jobs(g);
	// debug(g, 0);
	// debug(g, 1);
	// debug(g, 2);
	// debug(g, 3);
	// debug(g, 4);
	// teub = split(s, " ");
	// printf("teub[0] = %s\n teub[1] = %s\n", teub[0], teub [1]);
	// printf("CMD NOW = %s\n", s);
	// exec_cmd(teub);
}
