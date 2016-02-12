/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   src/paramss.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpoujade <lpoujade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/11 23:37:35 by lpoujade          #+#    #+#             */
/*   Updated: 2016/02/12 19:14:06 by lpoujade         ###   ########.fr       */
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
			opts |= 0001;
		else if (*av == 'r')
			opts |= 0010;
		else if (*av == 'R')
			opts |= 0100;
		else if (*av == 'a')
			opts |= 1000;
		else if (*av == 't')
			opts |= 10000;
		av++;
	}
	return (opts);
}