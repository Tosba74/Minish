/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_whitespaces.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmangin <bmangin@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/11 19:10:27 by bmangin           #+#    #+#             */
/*   Updated: 2021/11/28 15:25:38 by bmangin          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_len_words(char const *s, int pos)
{
	size_t	i;

	i = 0;
	while (s[pos + i] && ft_isspace(s[pos + i]))
		i++;
	return (i);
}

static int	ft_nb_words(char const *s)
{
	int	i;
	int	nb;

	i = 0;
	nb = 0;
	if (s == NULL)
		return (i);
	while (s[i] && ft_isspace(s[i]))
		i++;
	while (s[i])
	{
		if ((s[i + 1] == '\0' || ft_isspace(s[i + 1]))
			&& ft_isspace(s[i]))
			nb++;
		i++;
	}
	return (nb);
}

static char	**ft_free_all(char **teub, int t)
{
	free_all(teub, t);
	return (NULL);
}

static char	*ft_new_words(char const *s, int *index)
{
	int		i;
	char	*str;

	i = 0;
	str = wrmalloc(sizeof(char) * (ft_len_words(s, *index) + 1));
	while (s[*index] && ft_isspace(s[*index]))
		str[i++] = s[(*index)++];
	str[i] = '\0';
	return (str);
}

char	**ft_split_whitespaces(char const *s)
{
	int		i;
	int		t;
	int		nb_words;
	char	**teub;

	i = 0;
	t = -1;
	nb_words = ft_nb_words(s);
	teub = wrmalloc(sizeof(char *) * (nb_words + 1));
	while (++t < nb_words)
	{
		while (s[i] && ft_isspace(s[i]))
			i++;
		if (!ft_isspace(s[i]))
		{
			teub[t] = ft_new_words(s, &i);
			if (!(teub[t]))
				return (ft_free_all(teub, t));
		}
	}
	teub[t] = NULL;
	return (teub);
}
