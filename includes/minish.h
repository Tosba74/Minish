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

# include "libft.h"
# include "error.h"

typedef struct  s_dlst
{
	void            *content;
	struct s_dlst	*next;
	struct s_dlst	*back;
}   				t_dlst;

#endif
