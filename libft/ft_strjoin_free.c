/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_free.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: machoffa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/24 16:26:38 by machoffa          #+#    #+#             */
/*   Updated: 2020/01/17 16:42:13 by mreveret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin_free(char *s1, char *s2, int j)
{
	char	*dst;
	int		i;

	i = 0;
	if (!(s1) || !(s2))
		return (NULL);
	if (s1[i] == '\0' && s2[i] == '\0')
		return (ft_strnew(0));
	if (!(dst = ft_strnew(ft_strlen(s1) + ft_strlen(s2))))
		return (NULL);
	ft_strcpy(dst, s1);
	ft_strcat(dst, s2);
	if (j == 1)
		free(s1);
	if (j == 2)
		free(s2);
	if (j == 3)
	{
		free(s1);
		free(s2);
	}
	return (dst);
}
