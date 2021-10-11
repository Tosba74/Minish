/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmangin <bmangin@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/14 19:07:50 by bmangin           #+#    #+#             */
/*   Updated: 2021/09/24 23:37:40 by bmangin          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minish.h"

void	debug(t_global *g, int i)
{
	void	(*pf[5])(t_global *g);

	pf[0] = &print_env;
	pf[1] = &print_env_teub;
	pf[2] = &print_hidden;
	pf[3] = &print_story;
	pf[4] = &print_pipestruct;
	if (g->debug == true)
		pf[i](g);
}
