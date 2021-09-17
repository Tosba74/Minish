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

# include "libft.h"
# include "error.h"
# include "tools.h"

/*********************************************************/
/******************      BULTIN       ********************/
/*********************************************************/

/*********************************************************/
/******************      ENGINE       ********************/
/*********************************************************/

void		exec_cmd(char **cmd);

/*********************************************************/
/******************      PARSING      ********************/
/*********************************************************/

int			is_spec_char(char c);
void		parser(char *s);
void		init_env(t_global *g, char **env);
void		print_envp(char **env);
char		**get_env_tab(t_env *env);

/*********************************************************/
/******************       MAIN        ********************/
/*********************************************************/

void		ft_err(char *s, int err);
void		debug(t_global *g, int i);
const char	*prompt(void);

#endif
