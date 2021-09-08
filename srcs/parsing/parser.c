/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmangin <bmangin@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/08 02:00:38 by bmangin           #+#    #+#             */
/*   Updated: 2021/09/08 02:57:26 by bmangin          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minish.h"

void	parser(char *s)
{
	int		i;
	int		j;
	char	**tab;

	i = -1;
	j = -1;
	tab = ft_split(s, 32);
	if (!tab)
		printf("JPE PO TD BRO!");
	while (*tab[++i])
	{
		while (tab[i][++j])
			if (is_spec_char(tab[i][j]) != -1)
				printf("Moue et apres ?");
	}
}
