/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: machoffa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/07 19:08:13 by machoffa          #+#    #+#             */
/*   Updated: 2019/04/15 18:57:39 by machoffa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmap(char const *s, char (*f)(char))
{
	char	*dst;
	int		i;

	i = 0;
	if (!(s))
		return (NULL);
	if (!(dst = ft_strnew(ft_strlen(s))))
		return (NULL);
	while (s[i])
	{
		dst[i] = (*f)(s[i]);
		i++;
	}
	dst[i] = '\0';
	return (dst);
}
