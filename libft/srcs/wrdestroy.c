/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wrdestroy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmangin <bmangin@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/02 14:22:33 by bmangin           #+#    #+#             */
/*   Updated: 2021/11/29 16:26:17 by bmangin          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static t_list	**wrgetter(void)
{
	static t_list	*wrm;

	return (&wrm);
}

void	*wrmalloc(unsigned long size)
{
	char	*buffer;
	t_list	*new_elem;

	buffer = malloc(size);
	if (!buffer)
	{
		wrdestroy();
		ft_putstr_fd("Insufficient memory\n", 2);
		exit(ENOMEM);
	}
	new_elem = malloc(sizeof(t_list));
	if (!new_elem)
	{
		free(buffer);
		wrdestroy();
		ft_putstr_fd("Insufficient memory\n", 2);
		exit(ENOMEM);
	}
	new_elem->content = buffer;
	new_elem->next = 0;
	ft_lstadd_back(wrgetter(), new_elem);
	return (buffer);
}

int	wrfree(void *ptr)
{
	t_list	*prev;
	t_list	*current;
	t_list	*next;
	t_list	**wrstart;

	prev = 0;
	wrstart = wrgetter();
	current = *wrstart;
	while (current)
	{
		next = current->next;
		if (current->content == ptr)
		{
			free(ptr);
			free(current);
			if (prev)
				prev->next = next;
			else
				*wrstart = next;
			return (1);
		}
		prev = current;
		current = current->next;
	}
	return (0);
}

void	wrdestroy(void)
{
	t_list	*current;
	t_list	*next;
	t_list	**wrstart;

	wrstart = wrgetter();
	current = *wrstart;
	while (current)
	{
		next = current->next;
		printf("c.c\t\t\t%p\n", current->content);
		free(current->content);
		printf("c\t\t\t%p\n", current);
		free(current);
		current = next;
	}
	*wrstart = 0;
}
