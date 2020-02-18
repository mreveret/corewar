/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: machoffa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/08 15:54:10 by machoffa          #+#    #+#             */
/*   Updated: 2019/04/24 14:31:49 by machoffa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		count_word(const char *s, char c)
{
	int		i;
	int		j;

	i = 0;
	if (s[i] == '\0')
		return (0);
	j = 1;
	while (s[i])
	{
		if (s[i + 1] == c)
			j++;
		while (s[i + 1] && s[i + 1] == c)
			i++;
		i++;
	}
	return (j);
}

static int		start_word(const char *s, int i, char c)
{
	while (s[i] && s[i] != c)
		i++;
	while (s[i] && s[i] == c)
		i++;
	return (i);
}

static int		count_letter(const char *s, int i, char c)
{
	int k;

	k = 0;
	while (s[i] && s[i] != c)
	{
		k++;
		i++;
	}
	return (k);
}

char			**ft_strsplit(char const *s, char c)
{
	int		i;
	int		j;
	int		k;
	char	**tab;

	i = 0;
	s = ft_strtrimc(s, c);
	if ((!(s) || !(c)))
		return (NULL);
	j = count_word(s, c);
	if (!(tab = (char **)ft_memalloc(sizeof(char *) * (j + 1))))
		return (NULL);
	j = 0;
	while (j < count_word(s, c))
	{
		k = count_letter(s, i, c);
		if (!(tab[j] = (char *)ft_memalloc(sizeof(char) * (k + 1))))
			return (NULL);
		tab[j] = ft_strncpy(tab[j], s + i, k);
		i = start_word(s, i, c);
		j++;
	}
	tab[j] = 0;
	return (tab);
}
