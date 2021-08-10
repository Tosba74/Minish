/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmangin <bmangin@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/15 18:33:12 by bmangin           #+#    #+#             */
/*   Updated: 2021/07/11 21:27:31y bmangin          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minish.h"

/*
static const t_err  *err_pars(int err)
{
	static const t_err  err_p[] = {
	{ERRNO_DEF, "\n"},
	//{ERRNO_DEF, "\n"},
	// ...},
	};
	return (err_p[err]);
}

static const t_err  *err_exec(int err)
{
	static const t_err  err_e[] = {
	{ERRNO_DEF, "\n"},
	//{ERRNO_DEF, "\n"},
	// ...},
	};
	return(err_e(err));
}

void	ft_err(char *s, int err)
{
	ft_putstr_fd("Error:\n", 2);
	ft_putstr_fd(s, 2);
    if (!(err / 10))
	    ft_putstr_fd((char *)err_pars(err % 10), 2);
    else if (err / 10)
	    ft_putstr_fd((char *)err_exec(err % 10), 2);
	wrdestroy();
	exit(0);
}
*/