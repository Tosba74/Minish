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
# include <errno.h>

# define FIN -1
# define ERRNO_DEF 0

typedef struct  s_err
{
	int     err;
	char    *next;
}   			t_err;

#endif
