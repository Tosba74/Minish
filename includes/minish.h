#ifndef MINISH_H
# define MINISH_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <errno.h>

# include <curses.h>
# include <term.h>

# include "libft.h"
# include "error.h"
# include "tools.h"

/*********************************************************/
/*******************      GLOBAL      ********************/
/*********************************************************/

typedef struct s_global
{
	size_t		nb_proc;
	pid_t		pid_ar[1024];
	t_env		*env;
	t_env		*hidden;
	char		**envp;
	bool		hide_mod;
	bool		debug;
	t_story		*history;
	t_pipe		*pipe;
	int			err;
}	t_global;

extern t_global	*g_g;
extern bool		g_debug;

/*********************************************************/
/******************      BUILTIN      ********************/
/*********************************************************/

void		env(t_global *g);
void		pwd(t_global *g);
int			do_echo(t_job *j);
void		history(void);

/*********************************************************/
/******************      ENGINE       ********************/
/*********************************************************/

int			exec(t_pipe *pipe);
int			is_builtin(char *s);
void		simple_cmd(t_pipe *pipe);
void		dup_close(int src, int dst, char *s);

/*********************************************************/
/******************      PARSING      ********************/
/*********************************************************/

int			is_spec_char(char c);
char		*search_in_env(char *var);
int			count_this_char(char *s, char c);
void		lexer(t_token **tok, char *input);
void		parser(t_pipe *pipe);
void		init_env(char **env);
void		print_envp(char **env);
char		*get_last_input(void);
char		**get_env_teub(t_env *env);

/*********************************************************/
/******************       MAIN        ********************/
/*********************************************************/

void		debug(int i);

#endif
