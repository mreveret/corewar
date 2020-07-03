/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: machoffa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/11 12:25:19 by machoffa          #+#    #+#             */
/*   Updated: 2019/04/11 12:37:26 by machoffa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*cpy_s;

	cpy_s = (unsigned char *)s;
	i = 0;
	while (i < n)
	{
		if (cpy_s[i] == (unsigned char)c)
			return (cpy_s + i);
		i++;
	}
	return (NULL);
}
