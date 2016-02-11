/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   src/paramss.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpoujade <lpoujade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/11 23:37:35 by lpoujade          #+#    #+#             */
/*   Updated: 2016/02/11 23:37:35 by lpoujade         ###   ######## fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_params	parse_args(char **av, int ac)
{
	t_params	opts;

	opts = 0;

	while (--ac)
	{
		if (*av == '-')
			while(*av)
			{
				if (*av == 'R');
				if (*av == 'r');
				if (*av == 'l');
				if (*av == 'a');
				if (*av == 't');

				av++;
			}
		else
			longs_args_parse(av);
	}
}
