/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpoujade <lpoujade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/01 12:26:28 by lpoujade          #+#    #+#             */
/*   Updated: 2016/06/06 13:33:01 by lpoujade         ###   ########.fr       */
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
	int		earg;
	t_files	*list;

	ap = 0;
	earg = 0;
	list = NULL;
	while (++ap < ac)
		if (*av[ap] == '-' && !earg)
			*(av[ap] + 1) == '-' ? earg = 1 : (*opts |= parse_args(av[ap] + 1));
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
		if (list->fcount && !list->subfiles)
			unfold(list, opts);
		else if (!list->fcount && !(opts & REV_SORT))
			st_fputstr(list->details, list->fields_len);
		if (list->subfiles && !(opts & REV_SORT))
			recurse_out(list, opts);
		if (list->next)
			list = (t_files*)list->next;
		else
			break ;
	}
	if (opts & REV_SORT)
		rev_recurse_out(lastnode(list), opts);
	return (EXIT_SUCCESS);
}
