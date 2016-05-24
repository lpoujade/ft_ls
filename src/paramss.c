/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   src/paramss.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpoujade <lpoujade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/11 23:37:35 by lpoujade          #+#    #+#             */
/*   Updated: 2016/05/24 11:41:50 by lpoujade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void	err_exit(char c)
{
	ft_putstr("ls : ");
	ft_putchar(c);
	ft_putstr(": ");
	ft_putendl(strerror(22));
	exit(EXIT_FAILURE);
}

t_params	parse_args(char *av)
{
	t_params	opts;
	short int	err;

	err = 0;
	opts = 0;
	while (*av)
	{
		*av == 'l' ? opts |= LONG_FORMAT : err++;
		*av == 'r' ? opts |= REV_SORT : err++;
		*av == 'R' ? opts |= RECURSIVE : err++;
		*av == 'a' ? opts |= ALL : err++;
		*av == 't' ? opts |= TIME_SORT : err++;
		*av == 'A' ? opts |= ALMOST_ALL : err++;
		*av == 'g' ? opts |= HIDE_OWNER | LONG_FORMAT : err++;
		*av == 'F' ? opts |= ADD_FTYPE : err++;
		*av == 'B' ? opts |= FULL_NAMES : err++;
		*av == '1' ? 0 : err++;
		err != 9 ? err_exit(*av) : (err = 0);
		av++;
	}
	return (opts);
}
