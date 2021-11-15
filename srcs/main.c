/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmangin <bmangin@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/15 18:33:12 by bmangin           #+#    #+#             */
/*   Updated: 2021/11/14 19:37:46by bmangin          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minish.h"

bool	g_debug = false;
int		g_err = 0;

static char	*create_prompt(void)
{
	static char	*prompt;
	char		*home;
	t_env		*pwd;

	if (prompt)
		wrfree(prompt);
	pwd = env_find_cell(get_var_env(), "PWD");
	home = search_in_env("HOME");
	if (!ft_strncmp(pwd->value, home, ft_strlen(home)))
		prompt = ft_strjoin_free("~", pwd->value + ft_strlen(home), 0);
	else
		prompt = ft_strdup(pwd->value);
	if (g_err == 0)
	{
		prompt = ft_strjoin_free("\033[34m", prompt, 2);
		prompt = ft_strjoin_free(prompt, "\033[0m\033[36m $\033[0m\033[34m>\033[0m ", 1);
	}	
	else
	{
		prompt = ft_strjoin_free("\033[33m", prompt, 2);
		prompt = ft_strjoin_free(prompt, "\033[0m\033[31m $\033[0m\033[33m>\033[0m ", 1);
	}
	return (prompt);
}

static void	init_global(t_global *g, int ac, char **av, char **env)
{
	g_debug = false;
	(void)g;
	if (ac == 2)
	{
		if (!ft_strncmp(av[1], "-debug", 6))
			g_debug = true;
		else
		{
			ft_err("Arg", 1);
			exit (g_err);
		}
	}
	init_env(env);
	debug(0);
	debug(1);
}

void	init_pipe_bluff(t_pipe **pipe, char *input)
{
	int		i;
	char	**tmp;
	
	i = 0;
	tmp = ft_split(input, '|');
	while (tmp[i])
	{
		addback_cell_pipe(pipe,
			new_cell_pipe(tmp[i], new_job(tmp[i])));
		i++;
	}
	// printf("inpo t %s\n", input);
	// printf("input %s == %s\n", pipe->pipe_line, pipe->job->job);
	// tmp = last_cell_pipe(g_g->pipe);
	// tmp->job->job = input;
	// tmp->job->av = ft_split(input, ' ');
}

static void	loop(t_global *g)
{
	int		i;
	char	*input;
	t_pipe	*pipe;
	// char	*prompt;

	i = 0;
	input = readline(create_prompt());
	// prompt = create_prompt();
	// input = readline(prompt);
	// free(prompt);
	while (input)
	{
		pipe = NULL;
		if (input[0])
		{
			add_history(input);
			addback_cell_history(get_history(),
				new_cell_history(skip_space(input), i++));
			parser(pipe);
			(void)g;
			// if (count_cell_pipe(pipe) == 1)
				// simple_cmd(pipe);
			// else
				// exec(g, pipe);
			// clear_pipeline(pipe);
			init_pipe_bluff(&pipe, input);
			// printf("input %s == %s\n", pipe->pipe_line, pipe->job->job);
			exec(g, pipe);
			clear_pipeline(pipe);
			debug(0);
		}
		wrfree(input);
		input = readline(create_prompt());
		// prompt = create_prompt();
		// input = readline(prompt);
		// free(prompt);
	}
}

int	main(int ac, char **av, char **env)
{
	t_global	g;

	g = (t_global){};; 
	if (ac > 2)
	{
		ft_err("Arg", 0);
		exit(1);
	}
	init_global(&g, ac, av, env);
	loop(&g);
	wrdestroy();
	return (g_err);
}
