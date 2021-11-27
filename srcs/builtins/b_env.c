/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_env.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmangin <bmangin@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/12 13:03:08 by bmangin           #+#    #+#             */
/*   Updated: 2021/11/27 14:39:20 by astucky          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minish.h"

void	print_envp(char **env, int out)
{
	int	i;

	i = -1;
	while (env[++i])
	{
		ft_putstr_fd(env[i], out);
		ft_putstr_fd("\n", out);
	}
}

int	env(t_job *j, int out)
{
	(void)j;
	print_envp(get_env_teub(*get_var_env(), 1), out);
	return (0);
}
