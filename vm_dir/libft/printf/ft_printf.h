/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: machoffa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/19 17:37:45 by machoffa          #+#    #+#             */
/*   Updated: 2019/10/19 12:24:41 by machoffa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <unistd.h>
# include <stdlib.h>
# define BUFF_S 2000

typedef struct			s_struct
{
	int					zero;
	int					plus;
	int					crash;
	int					crash3;
	char				fl[300];
	int					crash2;
	int					crash4;
	int					moins;
	int					spaces;
	int					o;
	int					x;
	int					xx;
	int					len;
	char				*type_s;
	long double			type_f;
	int					type_c;
	long long			type_d;
	unsigned long long	type_ud;
	int					ox;
	int					point;
	int					i;
	int					ret;
	int					champ;
	int					size_num;
	int					tp;
	int					tc;
	char				b[BUFF_S];
	int					m;
	int					cast;
	int					*tabi;
	char				**tab;
}						t_struct;

int						ft_printf(const char *format, ...);
void					findtyp(const char *format, va_list ap, t_struct *t);
void					type_d(t_struct *t);
void					type_pourcent(t_struct *t);
void					type_s(t_struct *t, va_list ap);
void					type_c(t_struct *t, va_list ap);
void					type_u(t_struct *t);
void					type_f(t_struct *t, va_list ap);
void					printfloat(t_struct *t, int j, int i);
void					bufatoi(t_struct *t, const char *format);
void					buffer(t_struct *t, char c, int i);
void					bufferstr(t_struct *t, char *s, int i);
void					options1(t_struct *t, const char *f, va_list ap);
int						lnbrbase(unsigned long long n, unsigned long long base);
void					itoabuf(t_struct *t, int base, char *cbase, int j);
int						ft_atoip(const char *str);
size_t					ft_strlenp(const		char *s);
int						lennbr(long long n);
void					bonus(t_struct *t, const char *f, va_list ap);
void					bonustab(t_struct *t, va_list ap, const char *f);

#endif
