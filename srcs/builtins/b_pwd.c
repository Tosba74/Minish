/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_pwd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmangin <bmangin@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/20 22:14:25 by bmangin           #+#    #+#             */
/*   Updated: 2021/11/26 21:59:55 by bmangin          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minish.h"

int	pwd(t_job *j, int out)
{
	t_env	*cpy;

	cpy = *get_var_env();
	(void)j;
	while (cpy)
	{
		if (!ft_strcmp(cpy->name, "PWD"))
		{
			ft_putstr_fd(cpy->value, out);
			ft_putstr_fd("\n", out);
		}
		cpy = cpy->next;
	}
	return (0);
}
