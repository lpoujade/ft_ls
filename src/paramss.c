/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   src/paramss.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpoujade <lpoujade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/11 23:37:35 by lpoujade          #+#    #+#             */
/*   Updated: 2016/03/27 21:06:00 by lpoujade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void	err_exit(char c)
{
	ft_putstr("ls : ");
	ft_putchar(c);
	ft_putstr(": ");
	ft_putendl(strerror(22));
	exit(1);
}

t_params	parse_args(char *av)
{
	t_params	opts;

	opts = 0;
	while (*av)
	{
		if (*av == 'l')
			opts |= LONG_FORMAT;
		else if (*av == 'r')
			opts |= REV_SORT;
		else if (*av == 'R')
			opts |= RECURSIVE;
		else if (*av == 'a')
			opts |= ALL;
		else if (*av == 't')
			opts |= TIME_SORT;
		else if (*av == 'A')
			opts |= ALMOST_ALL;
		else if (*av == 'h')
			opts |= HUMAN_READ;
		else if (*av == 'g')
			opts |= HIDE_OWNER | LONG_FORMAT;
		else if (*av == 'D')
			opts |= ONLY_FOLD;
		else if (*av == 'F')
			opts |= ADD_FTYPE;
		else
			err_exit(*av);
		av++;
	}
	return (opts);
}
