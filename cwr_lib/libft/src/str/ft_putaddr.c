/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putaddr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sikpenou <sikpenou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/02 15:45:41 by sikpenou          #+#    #+#             */
/*   Updated: 2020/02/24 19:37:38 by sikpenou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	ft_putaddr(void *addr)
{
	unsigned long	nb;

	nb = addr;
	ft_putnbr_base(nb, 16);
}
