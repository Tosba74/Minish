/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_cd.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmangin <bmangin@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/20 22:12:24 by bmangin           #+#    #+#             */
/*   Updated: 2021/11/23 10:45:19 by bmangin          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minish.h"

char	*get_tild(char *av)
{
	t_env	*home;
	char	*road;

	home = env_find_cell(get_var_env(), "HOME");
	road = ft_strdup(home->value);
	if (av && ft_strlen(av) > 1)
		road = ft_strjoin_free(home->value, av + 1, 0);
	return (road);
}

char	*get_path(char *path, char *av)
{
	int		len;
	char	*tmp;

	if (av[0] == '/')
		tmp = ft_strdup(av);
	else if (!ft_strncmp(av, "./", 2))
		tmp = ft_strdup(av + 2);
	else if (!ft_strncmp(av, "..", 2))
	{
		len = ft_strlen(ft_strrchr(path, '/'));
		tmp = ft_substr(path, 0, (ft_strlen(path) - len));
		if (ft_strlen(av) != 2)
			tmp = ft_strjoin_free(tmp, av + 2, 1);
	}
	else
	{
		tmp = ft_strjoin_free(path, "/", 0);
		tmp = ft_strjoin_free(tmp, av, 1);
	}
	return (tmp);
}

int	is_dir(char *road)
{
	int		fd_tmp;

	fd_tmp = open (road, O_DIRECTORY);
	if (fd_tmp < 0)
	{
		close(fd_tmp);
		return (1);
	}
	close(fd_tmp);
	return (0);
}	

int	if_is_dir(t_env *pwd, t_env *oldpwd, t_job *job, char *road)
{
	if (!is_dir(road))
	{
		env_edit_value(oldpwd, pwd->value);
		env_edit_value(pwd, road);
		return (0);
	}
	else
	{
		ft_err("cd", 6);
		ft_putstr_fd(job->av[1], 2);
		ft_putstr_fd("\n", 2);
		return (1);
	}
	return (0);
}

int	do_cd(t_job *j)
{
	t_env	*pwd;
	t_env	*oldpwd;
	char	*road;

	road = NULL;
	pwd = env_find_cell(get_var_env(), "PWD");
	oldpwd = env_find_cell(get_var_env(), "OLDPWD");
	if (!j->av[1] || (j->av[1] && !ft_strncmp(j->av[1], "~", 1)))
		road = get_tild(j->av[1]);
	else if (!ft_strcmp(j->av[1], "-"))
		road = ft_strdup((env_find_cell(get_var_env(), "OLDPWD"))->value);
	else if (j->av[1])
		road = get_path(pwd->value, j->av[1]);
	skip_slash(road);
	return (if_is_dir(pwd, oldpwd, j, road));
}
