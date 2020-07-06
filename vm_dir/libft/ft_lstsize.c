/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: machoffa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/11 18:18:10 by machoffa          #+#    #+#             */
/*   Updated: 2019/04/11 18:20:14 by machoffa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_lstsize(t_list *alst)
{
	int		i;

	i = 0;
	while (alst)
	{
		alst = alst->next;
		i++;
	}
	return (i);
}