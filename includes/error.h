/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmangin <bmangin@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/08 01:50:46 by bmangin           #+#    #+#             */
/*   Updated: 2021/10/20 19:31:42 by bmangin          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_H
# define ERROR_H

# define FIN -1
# define ERRNO_DEF 0

typedef struct s_err
{
	int		err;
	char	*strerror;
}	t_err;

void		ft_err(char *s, int err);

#endif
