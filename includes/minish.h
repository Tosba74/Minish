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
/******************      bultins       ********************/
/*********************************************************/

void		env(t_global *g);
void		pwd(t_global *g);
void		history(t_global *g);
void		print_story(t_global *g);

/*********************************************************/
/******************      ENGINE       ********************/
/*********************************************************/

void		exec_cmd(t_global *g, char **cmd);
void		is_bultins(t_global *g, char *s);
t_pipe		*new_cell_pipe(char *content);
void		addback_cell_pipe(t_pipe **pipe, t_pipe *new);
int			counter_pipe(char *s);

/*********************************************************/
/******************      PARSING      ********************/
/*********************************************************/

int			is_spec_char(char c);
int			count_this_char(char *s, char c);
void		lexer(t_global *g);
void		parser(t_global *g);
void		init_env(t_global *g, char **env);
void		print_envp(char **env);
char		*get_last_input(t_global *g);
char		**get_env_teub(t_env *env);

/*********************************************************/
/******************       MAIN        ********************/
/*********************************************************/

void		ft_err(t_global *g, char *s, int err);
void		debug(t_global *g, int i);
void		print_env(t_global *g);
void		print_env_teub(t_global *g);
void		print_hidden(t_global *g);
void		print_story(t_global *g);
void		print_token(t_global *g);
const char	*prompt(void);

#endif
