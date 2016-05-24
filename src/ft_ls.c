/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   src/ft_ls.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpoujade <lpoujade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/11 14:14:04 by lpoujade          #+#    #+#             */
/*   Updated: 2016/05/24 12:26:24 by lpoujade         ###   ########.fr       */
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
		rev_print_list(file_list);
	return (errno ? 1 : 0);
}

void	rev_print_list(t_fileinfo *start)
{
	t_fileinfo	*tmp;
	t_fileinfo	*dir_check;
	int			*s_local = NULL;
	int			bc = 0;

	tmp = start;
	while (tmp->next && ++bc)
		tmp = (t_fileinfo*)tmp->next;
	dir_check = tmp;
	while (tmp->prev)
	{
		while (dir_check->prev && (dir_check->fcount <= 0 || dir_check->fcount == -2))
			dir_check = (t_fileinfo*)dir_check->prev;
		if (!s_local)
			pdir_infos(dir_check, 0, &s_local);
		st_fputstr(tmp->details, dir_check->s_len);
		if ((tmp = (t_fileinfo*)tmp->prev))
			fts_delnode((t_fileinfo*)tmp->next);
		if (tmp)
			dir_check = (t_fileinfo*)tmp->prev;
	}
	if (tmp)
		st_fputstr(tmp->details, s_local);
}
