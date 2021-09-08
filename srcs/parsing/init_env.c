/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmangin <bmangin@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/08 19:10:12 by bmangin           #+#    #+#             */
/*   Updated: 2021/09/09 00:55:42 by bmangin          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minish.h"

static t_env	*split_content(char *s)
{
	char	**tab_tmp;
	t_env	*env;

	tab_tmp = ft_split(s, '=');
	if (ft_strslen(tab_tmp) != 2)
		printf("error env\n");
	env = wrmalloc(sizeof(t_env));
	env->name = tab_tmp[0];
	env->value = tab_tmp[1];
	wrfree(tab_tmp);
	printf("%s\n", s);
	printf("%s=%s\n", env->name, env->value);
	return (env);
}

void	init_env(t_list **lst, char **env)
{
	int		i;
	int		size;

	i = -1;
	size = ft_strslen(env);
	printf("size == %d\n", size);
	printf("%p\n", lst);
	// *lst = ft_lstnew(split_content(env[i]));
	while (++i < size - 1)
		ft_lstadd_back(lst, ft_lstnew(split_content(env[i])));
}
