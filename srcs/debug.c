/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmangin <bmangin@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/14 19:07:50 by bmangin           #+#    #+#             */
/*   Updated: 2021/09/14 19:16:23 by bmangin          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minish.h"

void	print_env(t_global *g, t_env **env)
{
	if (g->debug == true)
	{
		while ((*env)->next)
		{
			dprint(STDERR_FILENO,"|%s| = |%s|\n", (*env)->name, (*env)->value);
		}
	}
}
