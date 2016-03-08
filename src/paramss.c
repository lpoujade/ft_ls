/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   src/paramss.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpoujade <lpoujade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/11 23:37:35 by lpoujade          #+#    #+#             */
/*   Updated: 2016/02/15 22:15:37 by lpoujade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_params	parse_args(char *av)
{
	t_params	opts;

	opts = 0;
	while (*av)
	{
		if (*av == 'l')
			opts |= 0x01;
		else if (*av == 'r')
			opts |= 0x02;
		else if (*av == 'R')
			opts |= 0x04;
		else if (*av == 'a')
			opts |= 0x08;
		else if (*av == 't')
			opts |= 0x10;
		else if (*av == 'A')
			opts |= 0x20;
		else
		{
			errno = 22;
			return (0);
		}
		av++;
	}
	return (opts);
}
