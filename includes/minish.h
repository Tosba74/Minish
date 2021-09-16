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

/*
| ******************************************************* |
| *****************      BULTIN       ******************* |
| ******************************************************* |
*/

/*
| ******************************************************* |
| *****************      ENGINE       ******************* |
| ******************************************************* |
*/

void		exec_cmd(char **cmd);

/*
| ******************************************************* |
| *****************      PARSING      ******************* |
| ******************************************************* |
*/

int			is_spec_char(char c);
int			env_size(t_env *env);
void		parser(char *s);
void		init_env(t_global *g, char **env);
void		addback_cell_env(t_env **env, t_env *new);
t_env		*new_cell_env(char **content);

/*
| ******************************************************* |
| *****************       MAIN        ******************* |
| ******************************************************* |
*/

void		ft_err(char *s, int err);
void		debug(t_global *g, int i);
const char	*prompt(void);

#endif
