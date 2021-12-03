/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmangin <bmangin@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/19 15:25:08 by bmangin           #+#    #+#             */
/*   Updated: 2021/12/03 20:13:34 by astucky          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minish.h"

int	gnl(char **line)
{
	char	*buffer;
	int		i;
	int		r;
	char	c;

	i = 0;
	r = 0;
	buffer = (char *)wrmalloc(10000000);
	if (!buffer)
		return (-1);
	r = read(0, &c, 1);
	while (r && c != '\n' && c != '\0')
	{
		if (c != '\n' && c != '\0')
			buffer[i] = c;
		i++;
		r = read(0, &c, 1);
	}
	buffer[i] = '\n';
	buffer[++i] = '\0';
	*line = buffer;
	wrfree(buffer);
	return (r);
}

static void	daddy_heredoc(int fd_0, int fd_1)
{
		close(fd_1);
		dup2(fd_0, STDIN_FILENO);
		close(fd_0);
		wait(NULL);
}

void	here_doc(t_job *job, char *limiter)
{
	pid_t	reader;
	int		fd[2];
	char	*line;

	if (pipe(fd) == -1)
		ft_err("Heredoc: ", 3);
	reader = fork();
	if (reader == 0)
	{
		close(fd[0]);
		while (gnl(&line))
		{
			if (ft_strncmp(line, limiter, ft_strlen(limiter)) == 0)
			{
				close(fd[1]);
				exit(EXIT_SUCCESS);
			}
			job->av = ft_strsjoin(job->av, line);
			write(fd[1], line, ft_strlen(line));
		}
	}
	else
		daddy_heredoc(fd[0], fd[1]);
}
