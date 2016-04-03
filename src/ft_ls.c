/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   src/ft_ls.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpoujade <lpoujade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/11 14:14:04 by lpoujade          #+#    #+#             */
/*   Updated: 2016/04/03 13:34:25 by lpoujade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int		main(int ac, char **av)
{
	t_params	opts;
	int			ap;
	int			eargs;
	t_fileinfo	*file_list;
	int			c;

	c = 0;
	file_list = NULL;
	eargs = 0;
	opts = 0;
	ap = 0;
	while (++ap < ac)
		if (*av[ap] == '-' && !eargs)
			*(av[ap] + 1) == '-' ? eargs = 1 : (opts |= parse_args(av[ap] + 1));
		else
		{
			ft_lstinsert((t_list**)&file_list, fts_new(av[ap]),
					opts & TIME_SORT ? &ftime_cmp : &fts_strcmp);
			c++;
		}
	if (!file_list && ++c)
		ft_lstinsert((t_list**)&file_list, fts_new("."), &fts_strcmp);
	eval(&file_list, opts, c);
	return (errno ? 1 : 0);
}
