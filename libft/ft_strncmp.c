/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: machoffa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/05 21:44:23 by machoffa          #+#    #+#             */
/*   Updated: 2020/01/15 17:21:58 by machoffa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t i;

	i = 0;
	if (n == 0)
		return (-1);
	while (s1[i] && s2[i] && s1[i] == s2[i] && i < n - 1)
		i++;
	if (s1[i] - s2[i] == 0 && s2[i + 1] != '\0')
		return (-1);
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}
