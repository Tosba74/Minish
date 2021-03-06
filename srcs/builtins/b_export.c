/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_export.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmangin <bmangin@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/20 22:13:23 by bmangin           #+#    #+#             */
/*   Updated: 2021/11/28 01:19:31 by bmangin          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minish.h"

int	do_export(t_job *j, int out)
{
	t_env	*tmp;

	(void)out;
	if (j->av[1])
	{
		tmp = env_find_cell(get_var_env(), j->av[1]);
		if (tmp)
		{
			tmp->print = PRINT;
			return (0);
		}
	}
	return (1);
}
