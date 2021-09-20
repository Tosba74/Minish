/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmangin <bmangin@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/08 02:00:38 by bmangin           #+#    #+#             */
/*   Updated: 2021/09/20 10:55:22 by bmangin          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minish.h"

void	parser(t_global *g)
{
	char	*s;

	s = ft_strdup(get_last_input(g));
	if (!ft_strcmp(s, "history"))
		history(g);
	else if (!ft_strcmp(s, "env"))
		env(g);
	debug(g, 1);
	debug(g, 2);
	// tab = split(s, " ");
	// printf("tab[0] = %s\n tab[1] = %s\n", tab[0], tab [1]);
	printf("CMD NOW = %s\n", s);
	// exec_cmd(tab);
}
