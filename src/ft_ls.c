/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   src/ft_ls.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpoujade <lpoujade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/11 14:14:04 by lpoujade          #+#    #+#             */
/*   Updated: 2016/03/22 16:22:36 by lpoujade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void	ftls_del(void *no)
{
	t_fileinfo	*node;

	node = (t_fileinfo *)no;
	ft_strdel(&node->infos);
}

int		main(int ac, char **av)
{
	t_params	opts;
	int			ap;
	int			end_args;
	t_fileinfo	*file_list;
	int c;

	c = 0;
	file_list = NULL;
	end_args = 0;
	opts = 0;
	ap = 0;
	while (++ap < ac)
	{
		if (*av[ap] == '-' && !end_args)
			*(av[ap] + 1) == '-' ? end_args = 1 : (opts |= parse_args(av[ap]));
		else
		{
			fflist_add(&file_list, av[ap]);
			c++;
		}
	}
	if (!file_list)
		file_list = fold_list(".", opts);
	eval(&file_list, opts, c);
	ft_lstdel((t_list**)file_list, &ftls_del);
	if (file_list)
	{
		ft_putendl("not freed : ");
		ls_out(file_list, opts);
	}
	return (errno ? 1 : 0);
}
