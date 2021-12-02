/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmangin <bmangin@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/16 10:35:16 by bmangin           #+#    #+#             */
/*   Updated: 2021/12/02 16:20:12 by astucky          ###   ########lyon.fr   */
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

void	addback_cell_history(t_story **story, t_story *new)
{
	t_story	*last;

	last = last_cell_history(*story);
	if (last != NULL)
	{
		last->next = new;
		new->prev = last;
		new->index = last->index + 1;
	}
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
	static t_story	*story = 0;

	return (&story);
}
