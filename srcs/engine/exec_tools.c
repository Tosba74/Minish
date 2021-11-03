/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_tools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmangin <bmangin@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/08 18:46:17 by bmangin           #+#    #+#             */
/*   Updated: 2021/10/22 10:15:43 by bmangin          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minish.h"

void	dup_close(int src, int dst, char *s)
{
	if (dup2(src, dst) < 0)
		ft_err(s, 14);
	if (close (src) < 0)
		ft_err(s, 14);
}

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
			while (road_exec[i--])
				wrfree(road_exec[i]);
			wrfree(road_exec);
			return (tmp);
		}
		wrfree (tmp);
	}
	while (road_exec[i--])
		wrfree(road_exec[i]);
	wrfree(road_exec);
	return (NULL);
}

char	*select_env_path(char *av, char **env)
{
	char	*road;
	char	**tmp;
	char	**road_exec;

	road = NULL;
	tmp = ft_split(av, ' ');
	if (tmp)
	{
		road_exec = extract_path(env);
		if (road_exec)
			road = choose_good_path(road_exec, tmp[0]);
		wrfree (tmp);
	}
	return (road);
}