/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmangin <bmangin@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/16 10:35:16 by bmangin           #+#    #+#             */
/*   Updated: 2021/11/10 21:18:13 by bmangin          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minish.h"

t_story	*new_cell_history(char *content, int index)
{
	t_story	*new;

	new = wrmalloc(sizeof(t_story));
	new->index = index;
	new->cmd = skip_space(content);
	new->next = NULL;
	new->prev = NULL;
	return (new);
}

t_story	*last_cell_history(t_story *story)
{
	if (story == NULL)
		return (NULL);
	while (story->next != NULL)
		story = story->next;
	return (story);
}

static void	link_cell_history(t_story *last, t_story *new)
{
	last->next = new;
	new->prev = last;
	new->index = last->index + 1;
}

void	addback_cell_history(t_story **story, t_story *new)
{
	t_story	*last;

	last = last_cell_history(*story);
	if (last != NULL)
		link_cell_history(last, new);
	else
		*story = new;
}

char	*get_last_input(void)
{
	t_story		*story;

	story = last_cell_history(*get_history());
	return (story->cmd);
}

t_story	**get_history(void)
{
	static t_story	*story;

	return (&story);
}
