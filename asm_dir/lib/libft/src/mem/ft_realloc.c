/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skpn <skpn@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/05 15:43:11 by sikpenou          #+#    #+#             */
/*   Updated: 2020/07/13 22:10:36 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_realloc(char **zone, long curr_size, long to_add)
{
	char	*tmp;

	if (!(tmp = (char *)gc_malloc(curr_size + to_add)))
		return (ft_error("malloc error - ft_realloc - l 20"));
	ft_memcpy(tmp, *zone, curr_size);
	gc_free((void **)zone);
	*zone = tmp;
	return (EXIT_SUCCESS);
}
