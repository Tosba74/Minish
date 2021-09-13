/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_emil.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebellon <ebellon@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/09 16:31:45 by ebellon           #+#    #+#             */
/*   Updated: 2021/09/14 00:53:06 by ebellon          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

// compile with -lreadline

#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "libft/libft.h"

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

void ft_free_chartab(char **strs)
{
	int	i;

	i = 0;
	while (strs[i])
		free(strs[i++]);
	free(strs);
}

void	ft_print_tree(t_input_tree *tree)
{
	t_pipe_line	*pipe_line;
	t_job		*job;
	int			i;
	
	printf("user input : /* %s */\n", tree->user_input);
	printf("nb process : /* %d */\n", tree->nb_process);
	pipe_line = tree->lst_pipe_line;
	while (pipe_line)
	{
		printf("pipe line : /* %s */\n", pipe_line->pipe_line);
		printf("file in : /* %d */\n", pipe_line->fd_filein);
		printf("file out : /* %d */\n", pipe_line->fd_fileout);
		job = pipe_line->job;
		if (job)
		{
			printf("job : /* %s */\nflags : /* %d */\narg :\n", job->job, job->flags);
			i = 0;
			while (job->av[i])
				printf("	/* %s */\n", job->av[i++]);
		}
		pipe_line = pipe_line->next;
	}
}

t_pipe_line	*ft_pipe_last(t_pipe_line *pipe_line)
{
	if (!pipe_line)
		return (NULL);
	while (pipe_line->next)
		pipe_line = pipe_line->next;
	return (pipe_line);
}

void	ft_pipe_add_back(t_pipe_line **fst, t_pipe_line *new)
{
	t_pipe_line	*last;

	last = ft_pipe_last(*fst);
	if (!*fst)
		*fst = new;
	else
		last->next = new;
}

void	set_pipe_line(t_input_tree *tree, char *pipe_line)
{
	t_pipe_line	*new_pipe_line;

	new_pipe_line = malloc(sizeof(t_pipe_line));
	if (!pipe_line)
	{
		/*error malloc*/
		exit (1);
	}
	new_pipe_line->pipe_line = ft_strdup(pipe_line);
	if (1)
		new_pipe_line->fd_filein = -1;
	/* else check pour redir */
	if (1)
		new_pipe_line->fd_fileout = -1;
	/* else check pour redir */
	ft_pipe_add_back(&tree->lst_pipe_line, new_pipe_line);
}

void	pipe_line_parser(t_input_tree *tree)
{
	char	**pipe_line;
	int		i;

	i = 0;
	pipe_line = ft_split(tree->user_input, '|');
	if (!pipe_line[1])
		set_pipe_line(tree, tree->user_input);
	else
	{
		while (pipe_line[i])
			set_pipe_line(tree, pipe_line[i++]);
		ft_free_chartab(pipe_line);
	}
}

t_input_tree	*input_tree_parser(char *user_input)
{
	t_input_tree	*tree;
	
	tree = malloc(sizeof(t_input_tree));
	if (!tree || !user_input)
	{
		/*error malloc*/
		if (user_input)
			free(user_input);
		exit (1);
	}
	tree->user_input = ft_strdup(user_input);
	if (!tree->user_input)
	{
		/*error malloc*/
		free(user_input);
		exit (1);
	}
	free(user_input);
	pipe_line_parser(tree);
	return (tree);
}

int main(int ac, char **av, char **envp)
{
	char 			*user_input;
	t_input_tree	*tree;
	
	(void)ac;
	(void)av;
	user_input = readline("$> ");
	while (user_input)
	{
		// parse line
		printf("%s\n", user_input);
		tree = input_tree_parser(user_input);
		ft_print_tree(tree);
		user_input = readline("$> ");
	}
	return (1);
}