/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncasecmp.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: machoffa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 05:52:58 by machoffa          #+#    #+#             */
/*   Updated: 2019/04/25 11:26:17 by machoffa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_strncasecmp(const char *s1, const char *s2, size_t n)
{
	size_t i;

	i = 0;
	if (n == 0)
		return (0);
	while (s1[i] && s2[i] && i < n - 1 && (s1[i] == s2[i] || (ft_islower(s1[i])
					&& s1[i] == s2[i] + 32) || (ft_isupper(s1[i])
						&& s1[i] == s2[i] - 32)))
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}
