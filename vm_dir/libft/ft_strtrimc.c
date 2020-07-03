/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrimc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: machoffa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/08 16:10:03 by machoffa          #+#    #+#             */
/*   Updated: 2019/04/15 18:00:25 by machoffa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrimc(char const *s, char c)
{
	int		i;
	int		j;
	char	*dst;

	i = 0;
	if (!(s))
		return (NULL);
	if (!(j = ft_strlen(s) - 1))
		return (0);
	while (s[i] && (s[i] == c))
		i++;
	if (s[i] == '\0')
		return ("\0");
	while (j > 0 && (s[j] == c))
		j--;
	if (!(dst = ft_strnew(j - i + 1)))
		return (NULL);
	ft_strncpy(dst, s + i, j - i + 1);
	return (dst);
}
