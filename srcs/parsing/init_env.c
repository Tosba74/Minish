/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmangin <bmangin@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/08 19:10:12 by bmangin           #+#    #+#             */
/*   Updated: 2021/09/14 20:11:47 by bmangin          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minish.h"

static char	*split_content(char *s)
{
	char	**tab_tmp;
	int		i;
	int		index;
	int		stop;
	int		size;

	i = 0;
	index = 0;
	stop = 0;
	tab_tmp = (char **)wrmalloc(sizeof(char *) * 2)
	while (s[stop] != '=')
		stop++;
	tab_tmp[0] = wrmalloc(sizeof(char *) * (stop + 1));
	tab_tmp[1] = wrmalloc(sizeof(char *) * (size - stop));
	stop = 0;
	while (s[stop++])
	{
		if (s[stop] == '=')
		{
			if (index == 0)
			{
				tab_tmp[index][i] = 0;
				index++;
				i = 0;
			}
		}
		else
			tab_tmp[index][i] = s[stop];
	}
	dprintf(STDERR_FILENO, "%s = %s\n", tab_tmp[0], tab_tmp[1]);
	return (tab_tmp);
}

void	init_env(t_list **env, char **envp)
{
	int		i;
	int		size;

	i = -1;
	size = ft_strslen(envp);
	printf("size == %d\n", size);
	printf("%p\n", env);
	while (++i < size - 1)
		addback_cell_env(env, new_cell_env(split_content(envp[i])));
}
