/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   select_env_path.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmangin <bmangin@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/25 02:35:04 by bmangin           #+#    #+#             */
/*   Updated: 2021/07/25 20:36:06 by bmangin          ###   ########lyon.fr   */
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
			wrfree(road_exec);
			return (tmp);
		}
		wrfree (tmp);
	}
	wrfree(road_exec);
	return (NULL);
}

char	*select_env_path(char *av, char **env)
{
	char	*road;
	char	**tmp;

	road = NULL;
	tmp = ft_split(av, ' ');
	if (tmp)
	{
		road = choose_good_path(extract_path(env), tmp[0]);
		wrfree (tmp);
	}
	return (road);
}

/*
char	*select_env_path(char *av, char **env)
{
	int	i;
	int	fd_tmp;
	char	*s;
	char	*tmp;
	char	*tab_cmd;
	char	**tab;

	i = -1;
	s = NULL;
	while (env[++i])
	{
		if (!ft_strncmp("PATH=", env[i], 5))
			tab = ft_split(env[i], ':');
	}
	tab_cmd = ft_split(av , ' ');
	if (ft_strslen(tab_cmd) == 3)
	
		

	i = -1;
	while (tab[++i])
	{
		tmp = ft_strjoin(tab[i], av);
		fd_tmp = open(tmp, O_RDONLY | S_IRUSR | S_IRGRP | S_IROTH);
		if (fd_tmp > 0)
		{
			close(fd_tmp);
			return (tmp);
		}
		free (tmp);
		i++;
	}
	return (NULL);
}
*/