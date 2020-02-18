/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mreveret <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/12 15:46:53 by mreveret          #+#    #+#             */
/*   Updated: 2020/02/17 18:15:28 by mreveret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COREWAR_H

# define COREWAR_H

#include "libft/libft.h"

#include "op.h"
#include <fcntl.h>

typedef struct		s_player
{
	int				num;
	header_t		*header;
	char			*content;
}					t_player;

typedef struct		s_process
{
	int				carry;
	int				pc;
	int				reg[REG_NUMBER + 1];
}					t_process;

typedef struct		s_vm
{
	char			arene[MEM_SIZE];
	int				cycle_to_d;
	int				cycle_delta;
	int				nbp;
	t_player		*p[4];
	
}					t_vm;

#endif
