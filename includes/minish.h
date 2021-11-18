/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minish.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmangin <bmangin@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 16:10:35 by astucky           #+#    #+#             */
/*   Updated: 2021/11/18 18:22:30 by bmangin          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISH_H
# define MINISH_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <stdbool.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <errno.h>

# include "libft.h"
# include "error.h"
# include "tools.h"

/*********************************************************/
/*******************      GLOBAL      ********************/
/*********************************************************/

typedef struct s_global
{
	int			index;
	int			pipe_fd[2];
	pid_t		pids[1024];
	size_t		nb_proc;
	char 		**env;
	bool		debug;
}	t_global;

extern int		g_err;

/*********************************************************/
/******************      BUILTIN      ********************/
/*********************************************************/

int			do_echo(t_job *j);
int			do_cd(t_job *j);
int			pwd(t_job *j);
int			export(t_job *j);
int			unset(t_job *j);
int			env(t_job *j);
int			do_exit(t_job *j);
int			history(t_job *j);
int			is_builtin(char *s);
int			select_built(t_pipe *p);
void		skip_slash(char *av);

/*********************************************************/
/******************      ENGINE       ********************/
/*********************************************************/

void		exec(t_global *g, t_pipe *pipe);
int			waiting_pid(t_global *g);
int			simple_cmd(t_global *g, t_pipe *pipe);
void		dup_close(int src, int dst, char *s);

/*********************************************************/
/******************      PARSING      ********************/
/*********************************************************/

int			is_spec_char(char c);
char		*search_in_env(char *var);
void		lexer(t_token **tok, char *input);
void		parser(t_pipe **pipe);
void		init_env(char **env);
void		print_envp(char **env);
char		*get_last_input(void);
char		**get_env_teub(t_env *env, int print);

/*********************************************************/
/******************       MAIN        ********************/
/*********************************************************/

void		debug(t_global *g, int i);

#endif
