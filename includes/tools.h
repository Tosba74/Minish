/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmangin <bmangin@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/08 01:55:22 by bmangin           #+#    #+#             */
/*   Updated: 2021/11/18 00:15:57 by bmangin          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOOLS_H
# define TOOLS_H

# define PARS_SHIT "$?|@&;<>/'"

# include <stdbool.h>

typedef enum e_type
{
	ARG,
	QUOTE,
	DQUOTE,
	FILES,
	DIR,
	CMD,
	BUILTIN,
	OPT,
	DOLLAR,
	EGAL,
	REDIR_R,
	REDIR_RD,
	REDIR_L,
	REDIR_LD,
	PIPE,
	SPC,
	ERROR,
	EOINPUT
}	t_type;

typedef enum e_print
{
	PRINT,
	PAPRINT
}	t_print;

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
	t_print			print;
	struct s_env	*next;
}	t_env;

typedef struct s_job
{
	char			*job;
	char			**av;
	bool			is_cmd;
}	t_job;

typedef struct s_pipe
{
	char			*pipe_line; // ls -alR minish/
	int				fd_in;
	int				fd_out;
	bool			no_job;
	bool			in;
	bool			out;
	t_job			*job;
	struct s_pipe	*next;
}	t_pipe;


/*********************************************************/
/********************     DEBUG     **********************/
/*********************************************************/

void		print_env(void);
void		print_env_teub(void);
void		print_hidden(void);
void		print_story(void);
void		print_pipestruct(t_pipe *p);
void		print_token(t_token *tok);

/*********************************************************/
/******************   ENVIRONNEMENT   ********************/
/*********************************************************/

t_env		**get_var_env(void);
t_env		*new_cell_env(char **content, t_print print);
void		addback_cell_env(t_env **env, t_env *new);
int			env_size(t_env *env, int print);
t_env		*env_find_cell(t_env **env, char *name);
void		env_edit_value(t_env *env, char *value);
int			is_name_env(char c);

/*********************************************************/
/********************    HISTORY    **********************/
/*********************************************************/

t_story		*new_cell_history(char *content, int index);
t_story		*last_cell_history(t_story *story);
void		addback_cell_history(t_story **story, t_story *new);
t_story		**get_history(void);

/*********************************************************/
/********************     PIPE     ***********************/
/*********************************************************/

t_pipe		*new_cell_pipe(char *content, t_job *job);
t_pipe		*last_cell_pipe(t_pipe *pipe);
void		addback_cell_pipe(t_pipe **pipe, t_pipe *new);
int			count_cell_pipe(t_pipe *pipe);
void		clear_pipeline(t_pipe *pipe);
void		del_job(t_job *jobs);
t_job		*new_job(char *av);
void		print_pipe(t_pipe *p);

/*********************************************************/
/*******************   TOKENIZATOR   *********************/
/*********************************************************/

t_token		*new_cell_tok(char *content, t_type t);
t_token		*last_cell_tok(t_token *tok);
void		addback_cell_tok(t_token **tok, t_token *new);
void		join_cell_tok(t_token *tok);
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

void		check_quotes(t_token *token);
void		egal_exp(t_token *tok);
char		*join_all_tok(t_token *tok);
void		complet_pipeline(t_pipe *pipe, t_token *tok);
void		check_expansion(t_token *tok);

#endif
