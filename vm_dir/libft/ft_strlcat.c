/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: machoffa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/04 14:47:51 by machoffa          #+#    #+#             */
/*   Updated: 2019/04/05 22:22:38 by machoffa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	i;
	size_t	j;

	j = 0;
	while (dest[j] && j < size)
		j++;
	i = 0;
	while ((src[i]) && ((j + i + 1) < size))
	{
		dest[j + i] = src[i];
		++i;
	}
	if (j != size)
		dest[j + i] = '\0';
	while (src[i])
		++i;
	return (j + i);
}
