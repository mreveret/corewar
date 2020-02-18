/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: machoffa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/19 14:17:58 by machoffa          #+#    #+#             */
/*   Updated: 2019/04/24 14:55:17 by machoffa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_realloc(char *str, int size)
{
	char	*new;

	if (!(new = (char*)malloc(sizeof(char) * size)))
		return (NULL);
	new = ft_strcpy(new, str);
	free(str);
	return (new);
}
