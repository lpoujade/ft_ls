/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpoujade <lpoujade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/01 12:26:28 by lpoujade          #+#    #+#             */
/*   Updated: 2016/06/05 19:46:02 by lpoujade         ###   ########.fr       */
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
	while (list && !(opts & REV_SORT))
	{
		if (list->fcount && !list->subfiles)
			unfold(list, opts);
		else if (!list->fcount)
			st_fputstr(list->details, list->fields_len);
		if (list->subfiles)
			recurse_out(list, opts);
		list = (t_files*)list->next;
	}
	ft_lstiter((t_list*)list, fts_delnode);
	return (EXIT_SUCCESS);
}
