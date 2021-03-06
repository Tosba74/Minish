/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmangin <bmangin@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/06 14:59:41 by bmangin           #+#    #+#             */
/*   Updated: 2021/09/24 23:37:40 by bmangin          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_len_words(char const *s, char c, int pos)
{
	size_t	i;

	i = 0;
	while (s[pos + i] && s[pos + i] != c)
		i++;
	return (i);
}

static int	ft_nb_words(char const *s, char c)
{
	int	i;
	int	nb;

	i = 0;
	nb = 0;
	if (s == NULL)
		return (i);
	while (s[i] && s[i] == c)
		i++;
	while (s[i])
	{
		if ((s[i + 1] == '\0' || s[i + 1] == c)
			&& s[i] != c)
			nb++;
		i++;
	}
	return (nb);
}

static char	**ft_free_all(char **teub, int t)
{
	int	i;

	i = 0;
	while (i != t)
		wrfree(teub[i++]);
	wrfree(teub);
	return (teub);
}

static char	*ft_new_words(char const *s, int *index, char c)
{
	int		i;
	char	*str;

	i = 0;
	str = wrmalloc(sizeof(char) * (ft_len_words(s, c, *index) + 1));
	while (s[*index] && s[*index] != c)
		str[i++] = s[(*index)++];
	str[i] = '\0';
	return (str);
}

char	**ft_split(char const *s, char c)
{
	int		i;
	int		t;
	int		nb_words;
	char	**teub;

	i = 0;
	t = -1;
	nb_words = ft_nb_words(s, c);
	teub = wrmalloc(sizeof(char *) * (nb_words + 1));
	while (++t < nb_words)
	{
		while (s[i] && s[i] == c)
			i++;
		if (s[i] != c)
		{
			teub[t] = ft_new_words(s, &i, c);
			if (!(teub[t]))
				return (ft_free_all(teub, t));
		}
	}
	teub[t] = NULL;
	return (teub);
}
