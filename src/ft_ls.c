/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpoujade <lpoujade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/01 12:26:28 by lpoujade          #+#    #+#             */
/*   Updated: 2016/06/01 17:09:20 by lpoujade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

/*
** Loop on **argv list,
** fill opts with options
** for files : loads files infos and sort them in a list
** for folder: same, but get folder's files in a list
*/

t_files	*p_args(char const **av, int ac, t_params *opts)
{
	int		ap;
	int		eargs;
	t_files	*list;

	ap = 0;
	eargs = 0;
	list = NULL;
	while (++ap < ac)
		if (*av[ap] == '-' && !eargs)
			*(av[ap] + 1) == '-' ? eargs = 1 : (*opts |= parse_args(av[ap] + 1));
		else
			ft_lstinsert((t_list**)&list, fts_new(av[ap], *opts),
					*opts & TIME_SORT ? &fts_timecmp : &fts_strcmp);
	return (list);
}

int		main(int ac, char const **av)
{
	t_params	opts;
	t_files		*list;

	opts = 0;
	list = NULL;
	if (!(list = p_args(av, ac, &opts)))
		list = (t_files*)fts_new(".", opts);
	while (list)
	{
		st_fputstr(list->details, list->fields_len);
		list = (t_files*)list->next;
	}
	return (EXIT_SUCCESS);
}

/*
int		main(int ac, char **av)
{
	t_params	opts;
	int			ap;
	int			eargs;
	t_fileinfo	*file_list;
	int			c;

	c = 0;
	file_list = NULL;
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
*/
