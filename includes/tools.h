/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebellon <ebellon@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/08 01:55:22 by bmangin           #+#    #+#             */
/*   Updated: 2021/09/14 01:03:02 by ebellon          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOOLS_H
# define TOOLS_H

# define PARS_SHIT "$?|@&;<>/'"

typedef struct s_ree
{
	unsigned int	key;
	struct s_ree	*left;
	struct s_ree	*right;
}	t_ree;

typedef enum s_bool
{
	false,
	true
}	t_bool;

typedef struct s_env
{
	char			*name;
	char			*value;
	struct s_env	*next;
}	t_env;

typedef struct	s_job
{
	/* flags &args of job */
	char	*job;
	char	flags;
	char	**av;
	char	**envp;
}				t_job;


typedef struct	s_pipe_line
{
	char		*pipe_line;

	/* plusieurs redirections ouvre les fichier mais ne fait que la derniere init -1*/
	int					fd_filein;
	int					fd_fileout;

	int					pipe_fd[2];
	t_job				*job;
	struct	s_pipe_line	*next;
}				t_pipe_line;


typedef struct	s_input_tree
{
	char 		*user_input;
	pid_t		pid_ar[1024];
	size_t		nb_process;
	t_pipe_line *lst_pipe_line;
}				t_input_tree;

typedef struct s_global
{
	t_list	**env;
	t_ree	*tree;
}	t_global;


#endif
