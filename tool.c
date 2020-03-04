/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tool.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mreveret <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/18 18:11:32 by mreveret          #+#    #+#             */
/*   Updated: 2020/03/04 16:59:39 by mreveret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

char			*ft_strsubzero(char const *s, unsigned int start, size_t len)
{
	char	*dst;
	size_t	i;

	i = 0;
	//if (!(s))
	//	return (NULL);
	if (!(dst = ft_memalloc(len + 1)))
		return (NULL);
	while (i < len)
	{
		dst[i] = s[start];
		i++;
		start++;
	}
	dst[i] = '\0';
	return (dst);
}

t_process		*create_process(int id, int pc)
{
	t_process	*proc;
	int			i;
	if (!(proc = (t_process*)malloc(sizeof(t_process))))
		return (0);
	i = -1;
	proc->id = id;
	proc->pc = pc % MEM_SIZE;
	while (++i)
	{
		if (i == 1)
			proc->reg[i] = id;
		else
			proc->reg[i] = 0;
	}
	return (proc);
}
