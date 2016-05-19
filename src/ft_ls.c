/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   src/ft_ls.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpoujade <lpoujade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/11 14:14:04 by lpoujade          #+#    #+#             */
/*   Updated: 2016/05/18 17:10:32 by lpoujade         ###   ########.fr       */
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
	if ((eval(&file_list, opts, c)))
	{
		ft_putendl("REVERSE PRINTING");
		rev_print_list(file_list);
	}
	!(opts & LONG_FORMAT) ? ft_putchar('\n') : 0;
	return (errno ? 1 : 0);
}

void	rev_print_list(t_fileinfo *start)
{
	t_fileinfo	*tmp;
	t_fileinfo	*dir_check;

	tmp = start;
	while (tmp->next)
		tmp = (t_fileinfo*)tmp->next;
	dir_check = tmp;
	while (tmp)
	{
		while (dir_check->prev && dir_check->fcount == 0)
			dir_check = (t_fileinfo*)dir_check->prev;
		st_fputstr(tmp->details, dir_check->s_len);
		if (tmp->prev || *tmp->details[3])
			ft_putchar('\n');
		tmp = (t_fileinfo*)tmp->prev;
		if (tmp && tmp->fcount != 0)
			dir_check = (t_fileinfo*)tmp->prev;
	}
}
