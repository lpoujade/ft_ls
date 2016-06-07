/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpoujade <lpoujade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/01 12:26:28 by lpoujade          #+#    #+#             */
/*   Updated: 2016/06/07 12:52:38 by lpoujade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

/*
** Loop on **argv list,
** fill opts with options
** for files : loads file infos and insert file in a list, sorted as requested
** for folder: same, but get folder's files in a list
*/

t_files	*p_args(char const **av, int ac, t_params *opts)
{
	int		ap;
	int		earg;
	t_files	*list;
	t_files	*a;
	t_files	*false_subs;

	ap = 0;
	earg = 0;
	list = NULL;
	false_subs = NULL;
	while (++ap < ac)
		if (*av[ap] == '-' && !earg)
			*(av[ap] + 1) == '-' ? earg = 1 : (*opts |= parse_args(av[ap] + 1));
		else
		{
			if ((a = (t_files*)fts_new(av[ap], *opts))->fcount)
				ft_lstinsert((t_list**)&list, (t_list*)a,
						*opts & TIME_SORT ? &fts_timecmp : &fts_strcmp);
			else
				ft_lstinsert((t_list**)&false_subs, (t_list*)a,
						*opts & TIME_SORT ? &fts_timecmp : &fts_strcmp);
		}
	if (false_subs && list)
		ft_lstappend((t_list*)false_subs, (t_list*)list);
	if (false_subs)
		list = false_subs;
	a = false_subs;
	while (a && ac)
	{
		adjust_cols(a->fields_len, list->fields_len);
		adjust_cols(list->fields_len, a->fields_len);
		if (!(a = (t_files*)a->next) && ac--)
			a = false_subs;
	}
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
		if (!list->next && (opts & REV_SORT))
			break ;
		list = (t_files*)list->next;
	}
	if (opts & REV_SORT)
	{
		rev_print_slist(lastnode(list));
		rev_recurse_out(lastnode(list), opts);
	}
	//ft_lstiter((t_list*)list, &fts_delnode);
	return (EXIT_SUCCESS);
}
