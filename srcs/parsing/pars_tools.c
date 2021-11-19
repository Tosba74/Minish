/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_tools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmangin <bmangin@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/08 01:43:20 by bmangin           #+#    #+#             */
/*   Updated: 2021/11/18 20:16:56 by bmangin          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minish.h"

int	find_error(t_token *tok)
{
	t_token	*cpy;

	cpy = tok;
	while (cpy)
	{
		if (cpy->type == ERROR)
		{
			ft_err("syntax error", 5);
			ft_putstr_fd("`", 2);
			ft_putstr_fd(cpy->value, 2);
			ft_putstr_fd("'", 2);
			ft_putstr_fd("\n", 2);
			return (1);
		}
		cpy = cpy->next;
	}
	return (0);
}

int	is_name_env(char c)
{
	if (ft_isalpha(c) || ft_isdigit(c) || c == '_')
		return (1);
	return (0);
}
int	count_this_char(char *s, char c)
{
	int	i;
	int	counter;

	i = 0;
	counter = 0;
	while (s[++i])
		if (s[i] == c)
			counter++;
	return (counter);
}

char	*search_in_env(char *var)
{
	t_env	*env;

	env = *get_var_env();
	while (env)
	{
		if (!ft_strcmp(env->name, var))
			return (env->value);
		env = env->next;
	}
	return ("\n");
}
