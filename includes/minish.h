#ifndef MINISH_H
# define MINISH_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <math.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/stat.h>
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
void		parser(char *s);
void		init_env(t_list **lst, char **env);

/*
| ******************************************************* |
| *****************       MAIN        ******************* |
| ******************************************************* |
*/

void		ft_err(char *s, int err);
void		prompt(void);

#endif
