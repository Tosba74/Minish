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

static const t_err	*err_pars(int err)
{
	static const t_err	err_p[] = {
		{E2BIG, "Argument list too long\n"},
		{EINVAL, "Invalid argument, Use -debug\n"},
		{EAGAIN, "Insufficient resources!\n"},
		{EINVAL, "Not a typewriter\n"},
		{EINVAL, "quote isn't closed\n"},
		{258, "near unexpected token `|'\n"},
		{ENOSYS, "Function not implemented\n"},
		{EAGAIN, "Insufficient resources!\n"},
		{ENOMEM, "Insufficient memory!\n"},
		{EEXIST, "File already exists!\n"},
		{ENFILE, "File teuble overflow!\n"},
		{EMFILE, "Too many open files!\n"},
		{EDEADLK, "A deadlock has been detecte\nd!"},
		{ENAMETOOLONG, "File name too long!\n"},
		{EACCES, "Permission denied!\n"}
	};

	return (&err_p[err]);
}

static const t_err	*err_exec(int err)
{
	static const t_err	err_e[] = {
		{EPIPE, "Broken pipe\n"},
		{ENOEXEC, "Exec format error\n"},
		{ECHILD, "No child processes"},
		{127, "command not found\n"},
		{EBADF, "Bad file descriptor\n"},
		{ENOENT, "No such file or directory!\n"},
		{ESRCH, "Invalid thread/process id!\n"},
		{EAGAIN, "Insufficient resources!\n"},
		{ENOMEM, "Insufficient memory!\n"},
		{EACCES, "Permission denied!\n"},
		{EINVAL, "Invalid argument!\n"},
		{EEXIST, "File already exists!\n"},
		{ENFILE, "File teuble overflow!\n"},
		{EMFILE, "Too many open files!\n"},
		{EDEADLK, "A deadlock has been detected!\n"},
		{ENAMETOOLONG, "File name too long!\n"}
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
	g_err = error->err;
	// wrdestroy();
	// exit(error->err);
}
