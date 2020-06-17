/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skpn <skpn@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/12 15:46:53 by mreveret          #+#    #+#             */
/*   Updated: 2020/06/17 15:41:09 by skpn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COREWAR_H

# define COREWAR_H

#include "libft/libft.h"

#include "op.h"
#include <fcntl.h>
#include <stdio.h>
//#define malloc(x) NULL
#define PROCESS ((t_process *)list->content)
# define LOG_LIVE 1
# define LOG_CYCLE 2
# define LOG_OP 4
# define LOG_DEATH 8
# define LOG_PC 16

typedef struct		s_player
{
	int				num;
	header_t		header;
	char			content[CHAMP_MAX_SIZE + 1];
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
	int				last_live_cycle;
	int				op;
	int				encoded;
	int				enc[4];
	int				t_arg[3];
	int				arg[3];
	int				test;
}					t_process;

typedef struct		s_op
{
char				*name;
int					nb_arg;
int					type_arg[3];
int					opcode;
int					wait;
char				*name2;
int					encoded;
int					dir_size;
}					t_op;

extern t_op op_tab[17];

typedef struct		s_vm
{
	char	arene[MEM_SIZE];
	int				cycle_to_die;
	int				cycle_delta;
	int				cycle_to_check;
	int				nbp;
	t_player		p[4];
	int				opt[5];
	int				fd;
	int				dumpnb;
	int				pos_next_player;
	int				pos_add;
	t_list			*lst_process;
	int				nbr_live;
	int				max_check;
	int				nb_c;
	int				before_check;
	int				current_proc_id;
	t_list			*first_proc;
	int				winner;
	int				add;
	int				log;
}					t_vm;

int					exit_corewar(t_vm *x, int ret);
void				init_vm(t_vm *x);
char				*ft_itoa_base(int n, int base);
char				*ft_itoa_base2(int n, int base);
void				ft_dump(t_vm *x);
int					ft_convert(t_vm *x, t_list *list, int size);
int					ft_convert3(t_vm *x, int size, int pos);
int					parsingplayer(t_vm *x, t_player *p);
t_process			*create_process(t_vm *x, int id, int pc);
int					indx_mod(int *arg);
void				convert_arg(int *arg,int mod,t_list *list,t_vm *x);
void				rev_str(char *nb, unsigned int size);
void				num_players(t_vm *x);
int					create_player(t_vm *x);
int					parsingoption(char **av,int i, t_vm *x);
int					move_pc(int pc,int pcadd);
void				kill_process(t_list *list, t_vm *x);
void				do_op(t_list *list, t_vm *x, int op);
void				ft_error(int i);
int					parse_arg(t_list *list, t_vm *x);
void				op_fork(t_list *list, t_vm *x);
void				op_add(t_list *list, t_vm *x);
void				op_and(t_list *list, t_vm *x);
void				op_ld(t_list *list, t_vm *x);
void				op_ldi(t_list *list, t_vm *x);
void				op_live(t_list *list, t_vm *x);
void				op_or(t_list *list, t_vm *x);
void				op_sti(t_list *list, t_vm *x);
void				op_sub(t_list *list, t_vm *x);
void				op_xor(t_list *list, t_vm *x);
void				op_st(t_list *list, t_vm *x);
void				op_zjmp(t_list *list, t_vm *x);
void				op_lld(t_list *list, t_vm *x);
void				op_lldi(t_list *list, t_vm *x);
void				op_lfork(t_list *list, t_vm *x);
void				op_aff(t_list *list, t_vm *x);
void				num_players(t_vm *x);
int					create_player(t_vm *x);
int					parsingoption(char **av,int i, t_vm *x);

#endif
