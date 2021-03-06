/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   select_env_path.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmangin <bmangin@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/25 02:35:04 by bmangin           #+#    #+#             */
/*   Updated: 2021/11/30 17:06:53 by astucky          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	**extract_path(char **env)
{
	int		i;
	char	*tmp;
	char	**road_exec;

	i = -1;
	tmp = NULL;
	road_exec = NULL;
	while (env[++i])
	{
		if (!ft_strncmp("PATH=", env[i], 5))
		{
			tmp = ft_strdup(env[i] + 5);
			road_exec = ft_split(tmp, ':');
			wrfree(tmp);
			return (road_exec);
		}
	}
	return (road_exec);
}

static char	*choose_good_path(char **road_exec, char *av)
{
	int		i;
	int		fd_tmp;
	char	*tmp;

	i = -1;
	while (road_exec[++i])
	{
		tmp = ft_strjoin(road_exec[i], "/");
		tmp = ft_strjoin(tmp, av);
		if (tmp)
			fd_tmp = open(tmp, O_RDONLY | S_IRUSR | S_IRGRP | S_IROTH);
		if (fd_tmp > 0)
		{
			close(fd_tmp);
			while (i-- != 0)
				wrfree(road_exec[i]);
			wrfree(road_exec);
			return (tmp);
		}
		wrfree (tmp);
	}
	while (i-- != 0)
		wrfree(road_exec[i]);
	wrfree(road_exec);
	return (NULL);
}

char	*select_env_path(char *av, char **env)
{
	int		i;
	char	*road;
	char	**tmp;
	char	**road_exec;

	i = 0;
	road = NULL;
	tmp = ft_split(av, ' ');
	if (tmp)
	{
		road_exec = extract_path(env);
		if (road_exec)
			road = choose_good_path(road_exec, tmp[0]);
		while (tmp[i])
			wrfree(tmp[i++]);
		wrfree (tmp);
	}
	return (road);
}
