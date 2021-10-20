/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmangin <bmangin@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/08 01:55:22 by bmangin           #+#    #+#             */
/*   Updated: 2021/10/20 21:08:21 by bmangin          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOOLS_H
# define TOOLS_H

# define PARS_SHIT "$?|@&;<>/'"

# include <stdbool.h>

typedef enum e_type
{
	ARG,
	FILES,
	DIR,
	CMD,
	BUILTIN,
	OPT,
	QUOTE,
	DQUOTE,
	DOLLAR,
	EGAL,
	REDIR,
	PIPE,
	SPACE,
	ERROR,
	EOINPUT
}	t_type;

typedef struct s_token
{
	char			*value;
	t_type			type;
	struct s_token	*prev;
	struct s_token	*next;
}					t_token;

typedef struct s_story
{
	unsigned int	index;
	char			*cmd;
	struct s_story	*prev;
	struct s_story	*next;
}	t_story;

typedef struct s_env
{
	char			*name;
	char			*value;
	struct s_env	*next;
}	t_env;

typedef struct s_job
{
	char			*job; // /bin/ls
	char			*flags; // -alR
	char			**av; // {"ls", "-alR", "minish/"}
	char			**envp;
}	t_job;

typedef struct s_pipe
{
	char			*pipe_line; // ls -alR minish/
	int				fd_in;
	int				fd_out;
	int				pipe_fd[2];
	t_job			*job;
	struct s_pipe	*next;
}	t_pipe;

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

/*********************************************************/
/********************     DEBUG     **********************/
/*********************************************************/

void		print_env(void);
void		print_env_teub(void);
void		print_hidden(void);
void		print_story(void);
void		print_pipestruct(void);
void		print_token(t_token *tok);

/*********************************************************/
/******************   ENVIRONNEMENT   ********************/
/*********************************************************/

t_env		*new_cell_env(char **content);
void		addback_cell_env(t_env **env, t_env *new);
int			env_size(t_env *env);

/*********************************************************/
/********************    HISTORY    **********************/
/*********************************************************/

t_story		*new_cell_history(char *content, int index);
t_story		*last_cell_history(t_story *story);
void		addback_cell_history(t_story **story, t_story *new);

/*********************************************************/
/********************     PIPE     ***********************/
/*********************************************************/

t_pipe		*new_cell_pipe(char *content);
void		addback_cell_pipe(t_pipe **pipe, t_pipe *new);
int			count_cell_pipe(t_pipe *pipe);

/*********************************************************/
/*******************   TOKENIZATOR   *********************/
/*********************************************************/

t_token		*new_cell_tok(char *content, t_type t);
t_token		*last_cell_tok(t_token *tok);
void		addback_cell_tok(t_token **tok, t_token *new);
void		clear_tok(t_token *tok);
int			find_error(t_token *tok);
int			dollar_tok(t_token **tok, char *input);
int			quote_tok(t_token **tok, char *input);
int			space_tok(t_token **tok, char *input);
int			redir_tok(t_token **tok, char *input);
int			pipe_tok(t_token **tok, char *input);
int			egal_tok(t_token **tok, char *input);
int			option_tok(t_token **tok, char *input);
int			egal_tok(t_token **tok, char *input);

#endif
