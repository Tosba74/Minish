/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmangin <bmangin@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/15 18:33:12 by bmangin           #+#    #+#             */
/*   Updated: 2021/09/08 02:18:03 by bmangin          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minish.h"

int	main(void)
{
	char	*buf;
	size_t	buf_size;

	buf_size = 2048;
	buf = (char *)ft_calloc(sizeof(char), buf_size);
	prompt();
	while (getline(&buf, &buf_size, stdin) > 0)
	{
		printf("buf = %s\n", buf);
		parser(buf);
		prompt();
	}
	wrfree(buf);
}
