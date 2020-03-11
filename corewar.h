/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mreveret <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/12 15:46:53 by mreveret          #+#    #+#             */
/*   Updated: 2020/03/11 18:17:20 by mreveret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COREWAR_H

# define COREWAR_H

#include "libft/libft.h"

#include "op.h"
#include <fcntl.h>


#define PROCESS ((t_process *)list->content)

typedef struct		s_player
{
	int				num;
	header_t		*header;
	char			*content;
	int				alive;
	int				pcstart;
}					t_player;

typedef struct		s_process
{
	int				id;
	int				pc;
	int				reg[REG_NUMBER];
	int				carry;
	int				wait;
	int				alive;
	int				op;
	int				encoded;
	int				enc[4];
	int				t_arg[4];
	char			*arg[4];
	int				pc_arg;
}					t_process;

typedef struct		s_vm
{
	char			arene[MEM_SIZE];
	int				cycle_to_die;
	int				cycle_delta;
	int				cycle_to_check;
	int				nbp;
	t_player		p[4];
	int				opt[2];
	int				fd;
	int				pos_next_player;
	int				pos_add;
	t_list			*lst_process;
	int				nbr_live;
	int				max_check;
	int				nb_c;
	t_list			*first_proc;
}					t_vm;

void		init_vm(t_vm *x);
char	*ft_itoa_base(int n, int base);
char	*ft_itoa_base2(int n, int base);
void	ft_dump(t_vm *x);
#endif
