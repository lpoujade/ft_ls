/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   src/ft_ls.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpoujade <lpoujade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/11 14:14:04 by lpoujade          #+#    #+#             */
/*   Updated: 2016/03/24 20:13:56 by lpoujade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int		main(int ac, char **av)
{
	t_params	opts;
	int			ap;
	int			end_args;
	t_fileinfo	**file_list;
	t_fileinfo	*new;
	int c;

	c = 0;
	new = NULL;
	file_list = &new;
	end_args = 0;
	opts = 0;
	ap = 0;
	while (++ap < ac)
	{
		if (*av[ap] == '-' && !end_args)
			*(av[ap] + 1) == '-' ? end_args = 1 : (opts |= parse_args(av[ap] + 1));
		else
		{
			ft_lstinsert((t_list**)file_list, fts_new(av[ap]), &fts_strcmp);
			c++;
		}
	}
	if (!*file_list && ++c)
		ft_lstinsert((t_list**)file_list, fts_new("."), &fts_strcmp);
	eval(file_list, opts, c);

//	ft_lstdel((t_list**)file_list, &ftls_del);
//	if (file_list)
//	{
//		ft_putendl("not freed : ");
//		ls_out(file_list, opts);
//	}
	return (errno ? 1 : 0);
}
