/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmangin <bmangin@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/08 01:55:22 by bmangin           #+#    #+#             */
/*   Updated: 2021/10/17 19:22:02 by bmangin          ###   ########lyon.fr   */
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
	VAR,
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
	char			*job; // user input ?
	char			flags;
	char			**av;
	char			**envp;
}	t_job;

typedef struct s_pipe
{
	char			*pipe_line; // input ?
	int				fd_in;
	int				fd_out;
	int				pipe_fd[2];
	t_job			*job;
	struct s_pipe	*next;
}	t_pipe;

typedef struct s_global
{
	char 		*input; // don't use it for exec find this in lstlast(history)!!!!
	size_t		nb_process;
	pid_t		pid_ar[1024];
	t_env		*env;
	t_env		*hidden;
	t_token		*tok;
	bool		hide_mod;
	bool		debug;
	t_story		*history;
	t_pipe		*pipe;
	int			err;
}	t_global;

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
/*******************   TOKENIZATOR   *********************/
/*********************************************************/

t_token		*new_cell_tok(char *content, t_type t);
t_token		*last_cell_tok(t_token *tok);
void		addback_cell_tok(t_token **tok, t_token *new);
void		clear_tok(t_token *tok);
int			var_tok(t_token **tok, char *input);
int			quote_tok(t_token **tok, char *input);
int			space_tok(t_token **tok, char *input);
int			redir_tok(t_token **tok, char *input);
int			pipe_tok(t_token **tok, char *input);
int			option_tok(t_token **tok, char *input);
int			egal_tok(t_token **tok, char *input);
int			tokenizator(t_token **tok, char *input);

#endif
