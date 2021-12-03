/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmangin <bmangin@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/15 18:33:12 by bmangin           #+#    #+#             */
/*   Updated: 2021/12/03 20:24:04 by bmangin          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minish.h"

int		g_err = 0;

char	*create_prompt(void)
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
		prompt = ft_strjoin_free(prompt,
				"\033[0m\033[36m $\033[0m\033[34m>\033[0m ", 1);
	}	
	else
	{
		prompt = ft_strjoin_free("\033[33m", prompt, 2);
		prompt = ft_strjoin_free(prompt,
				"\033[0m\033[31m $\033[0m\033[33m>\033[0m ", 1);
	}
	return (prompt);
}

static void	init_pids(t_global *g)
{
	int		i;

	i = 0;
	while (i < 1024)
	{
		get_pid_exec()->pids[i] = 0;
		i++;
	}
	g->nb_proc = 0;
	g->pipe_fd[0] = 0;
	g->pipe_fd[1] = 1;
	get_pid_exec()->index = 0;
	get_pid_exec()->no_job = false;
	get_pid_exec()->exit = false;
	sigignore(SIGQUIT);
	signal(SIGINT, &handler_idle);
}

static void	init_global(t_global *g, int ac, char **av, char **env)
{
	g->debug = false;
	if (ac == 2)
	{
		if (!ft_strncmp(av[1], "-debug", 6))
			g->debug = true;
		else
		{
			ft_err("Arg", 1);
			exit (g_err);
		}
	}
	init_env(env);
}

static void	loop(t_global *g)
{
	unsigned int	i;
	char			*input;
	t_pipe			*pipe;

	i = 0;
	sigignore(SIGQUIT);
	signal(SIGINT, &handler_idle);
	input = readline(create_prompt());
	while (input)
	{
		init_pids(g);
		pipe = NULL;
		if (input[0])
		{
			add_history(input);
			parser(&pipe, input, &i);
			g->nb_proc = count_cell_pipe(pipe);
			if (g->nb_proc > 0 && !get_pid_exec()->no_job)
				exec(g, pipe);
			clear_pipeline(pipe);
		}
		ft_memdel((void **)&input);
		if (!get_pid_exec()->exit)
			input = readline(create_prompt());
	}
}

int	main(int ac, char **av, char **env)
{
	t_global	*g;

	g = &(t_global){0};
	g_err = 0;
	if (ac > 2)
	{
		ft_err("Arg", 0);
		exit(1);
	}
	init_global(g, ac, av, env);
	loop(g);
	wrdestroy();
	return (g_err);
}
