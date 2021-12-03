/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astucky <astucky@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/03 16:24:58 by astucky           #+#    #+#             */
/*   Updated: 2021/12/03 16:25:50 by astucky          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minish.h"

static const t_err	*err_pars(int err)
{
	static const t_err	err_p[] = {
	{E2BIG, "Argument list too long\n"},
	{EINVAL, "Invalid argument, Use -debug\n"},
	{EAGAIN, "Insufficient resources!\n"},
	{EINVAL, "Not a typewriter\n"},
	{EINVAL, "quote isn't closed\n"},
	{258, "near unexpected token "},
	{1, "no such file or directory\n"},
	{1, "Permission denied\n"},
	{1, "Is a directory\n"},
	{1, "ambigous redirect\n"}
	};

	return (&err_p[err]);
}

static const t_err	*err_exec(int err)
{
	static const t_err	err_e[] = {
	{EPIPE, "Broken pipe\n"},
	{ENOEXEC, "Exec format error\n"},
	{ECHILD, "No child processes\n"},
	{127, "command not found\n"},
	{EBADF, "Bad file descriptor\n"},
	{ENOENT, "No such file or directory!\n"},
	{1, "File name too long\n"}
	};

	return (&err_e[err]);
}

void	ft_err(char *s, int err)
{
	t_err	*error;

	error = NULL;
	if (!(err / 10))
		error = (t_err *)err_pars(err);
	else if (err / 10)
		error = (t_err *)err_exec(err % 10);
	ft_putstr_fd("\033[31mError:\033[0m\n", 2);
	ft_putstr_fd(s, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd((char *)error->strerror, 2);
	if (!g_err)
		g_err = error->err;
}
