/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmangin <bmangin@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/08 02:00:38 by bmangin           #+#    #+#             */
/*   Updated: 2021/09/17 09:35:03 by bmangin          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minish.h"

static char	**split(char *raw_cmd, char *limit)
{
	char	*ptr;
	char	**cmd;
	size_t	idx;

	ptr = strtok(raw_cmd, limit);
	cmd = NULL;
	idx = 0;
	while (ptr)
	{
		cmd = (char **)realloc(cmd, ((idx + 1) * sizeof(char *)));
		cmd[idx] = strdup(ptr);
		ptr = strtok(NULL, limit);
		++idx;
	}
	cmd = (char **)realloc(cmd, ((idx + 1) * sizeof(char *)));
	cmd[idx] = NULL;
	return (cmd);
}

static void	free_array(char **array)
{
	int	i;

	i = -1;
	while (array[++i])
	{
		wrfree(array[i]);
		array[i] = NULL;
	}
	wrfree(array);
	array = NULL;
}

void	parser(char *s)
{
	char	**tab;

	tab = NULL;
	tab = split(s, " ");
	printf("tab[0] = %s\n tab[1] = %s\n", tab[0], tab [1]);
	printf("CMD NOW\n");
	exec_cmd(tab);
	free_array(tab);
	/*
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
	*/
}
