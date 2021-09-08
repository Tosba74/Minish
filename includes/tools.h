/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmangin <bmangin@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/08 01:55:22 by bmangin           #+#    #+#             */
/*   Updated: 2021/09/08 23:37:52 by bmangin          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOOLS_H
# define TOOLS_H

# define PARS_SHIT "$?|@&;<>/'"

typedef struct s_ree
{
	unsigned int	key;
	struct s_ree	*left;
	struct s_ree	*right;
}	t_ree;

typedef enum s_bool
{
	false,
	true
}	t_bool;

typedef struct s_env
{
	char			*name;
	char			*value;
}	t_env;

typedef struct s_global
{
	t_list	**env;
	t_ree	*tree;
}	t_global;

#endif
