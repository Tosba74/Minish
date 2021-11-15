/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_pwd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmangin <bmangin@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/20 22:14:25 by bmangin           #+#    #+#             */
/*   Updated: 2021/11/15 21:59:52 by bmangin          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minish.h"

int	pwd(t_job *j)
{
	t_env	*cpy;

	cpy = *get_var_env();
	(void)j;
	while (cpy)
	{
		dprintf(STDERR_FILENO, "\033[32m%s = %s\033[0m\n", cpy->name, cpy->value);
		if (!ft_strcmp(cpy->name, "PWD"))
			printf("%s\n", cpy->value);
		cpy = cpy->next;
	}
	return (0);
}
