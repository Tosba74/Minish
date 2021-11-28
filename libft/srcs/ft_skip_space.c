/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_skip_space.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmangin <bmangin@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/22 18:20:38 by bmangin           #+#    #+#             */
/*   Updated: 2021/11/28 15:21:36 by bmangin          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*skip_space(char *s)
{
	unsigned int	i;
	size_t			stop;
	size_t			len;
	char			*buf;

	i = 0;
	buf = NULL;
	while (s[i] && s[i] == ' ')
		i++;
	stop = ft_strlen(s);
	while (s[--stop] && s[stop] == ' ')
		;
	len = (size_t)stop - i + 1;
	if (len > 0)
		buf = ft_substr(s, i, len);
	wrfree(s);
	return (buf);
}
