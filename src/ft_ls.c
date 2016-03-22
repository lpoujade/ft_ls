/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   src/ft_ls.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpoujade <lpoujade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/11 14:14:04 by lpoujade          #+#    #+#             */
/*   Updated: 2016/03/22 21:44:08 by lpoujade         ###   ########.fr       */
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
			*(av[ap] + 1) == '-' ? end_args = 1 : (opts |= parse_args(av[ap]));
		else
		{
			ft_lstinsert((t_list**)file_list, fts_new(av[ap]), &fts_strcmp);
			//ft_putstr((*file_list)->infos);ft_putendl("******");
			c++;
		}
	}
	if (!*file_list)
		new = fold_list(".", opts);
	eval(file_list, opts, c);
//	ft_lstdel((t_list**)file_list, &ftls_del);
//	if (file_list)
//	{
//		ft_putendl("not freed : ");
//		ls_out(file_list, opts);
//	}
	return (errno ? 1 : 0);
}
