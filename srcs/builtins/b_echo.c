/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_echo.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmangin <bmangin@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/20 22:11:48 by bmangin           #+#    #+#             */
/*   Updated: 2021/10/20 16:21:16 by bmangin          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minish.h"
/*
static int	no_return(char *str, int *j, int k)
{
	if (k)
		return (0);
	if (ft_strncmp(str, "-n", 2))
		return (0);
	str = str + 2;
	while (*str)
	{
		if (*str != 'n')
			return (0);
		str++;
	}
	*j += 1;
	return (1);
}

static void	trim_arg(char **args)
{
	int		i;

	i = -1;
	while (args[++i])
		;
	while (!ft_strlen(args[--i]) && get_all_st(NULL)->flag_quote == 0)
		args[i] = 0;
}

void		do_echo(char **args)
{
	int opt_flag;
	int i;
	int j;
	int k;

	j = 0;
	i = 0;
	k = 0;
	trim_arg(args);
	if (args[1])
	{
		if (no_return(args[1], &j, k))
			i++;
		while (args[++i])
		{
			if (!no_return(args[i], &j, k))
			{
				if (i - 1 == j)
					ft_putstr(args[i]);
				else
					ft_putstr(args[i]);
				k = 1;
			}
		}
	}
	if (!args[1] || !j)
		ft_putstr("\n");
	get_all_st(NULL)->state = 0;
}
*/
static int	no_return(char *str)
{
	if (ft_strncmp(str, "-n", 2))
		return (0);
	str = str + 2;
	while (*str)
	{
		if (*str != 'n')
			return (0);
		str++;
	}
	return (1);
}

void		do_echo(t_job *j)
{
	int	index;
	int	opt_flag;

	index = 1;
	if (j->av[index])
	{
		opt_flag = no_return(j->av[1]);
		if (opt_flag)
			index++;
		while (j->av[index])
			ft_putstr(j->av[index++]);
	}
	if (!j->av[index] && !opt_flag)
		ft_putstr("\n");
}
