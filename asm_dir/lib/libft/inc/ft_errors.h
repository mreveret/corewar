/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_errors.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skpn <skpn@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/08 14:35:21 by skpn              #+#    #+#             */
/*   Updated: 2020/07/13 21:53:45 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_ERRORS_H
# define FT_ERRORS_H

# define ERR_FD 2

# define ERR_LEN 60
# define ERR_TOTAL_LEN 900

# define ERR_MSG_FULL "Too many errors.\n"
# define ERR_MSG_FULL_LEN 17
# define ERR_TOO_LONG "... (error too long)\n"
# define ERR_TOO_LONG_LEN 21

typedef struct	s_err
{
	int			fd;
	int			pos;
	char		*msg;
}				t_err;

int				ft_error(char *new_error);

void			ft_errors_print(void);

void			ft_errors_set_fd(int fd);

#endif
