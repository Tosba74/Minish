/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmangin <bmangin@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/06 18:37:28 by bmangin           #+#    #+#             */
/*   Updated: 2021/08/16 16:28:56 by bmangin          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# define MAX_PROCCESS 1392
// ulimit -u

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include <stdbool.h>
# include <sys/types.h>
# include <sys/wait.h>

# include "../libft/includes/libft.h"

typedef struct s_pipex
{
	int		index;
	int		pipefd[2];
	int		fd_in;
	int		fd_out;
	char	*cmd;
	char	**av;
	char	**env;
	bool	in;
	bool	out;
	pid_t	pids[MAX_PROCCESS];
}	t_pipex;

// tool.c
void	ft_err(char *s, int err);
void	init_bool(t_pipex *p, int index, int ac);
void	init_cmd(t_pipex *p, char *av);
void	dup_close(int src, int dst, char *s);

// pipex.c
int		exec(t_pipex *p, int ac, char **av, char **env);

void	ft_print_fd(int fd);
#endif
