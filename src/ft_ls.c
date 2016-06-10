/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpoujade <lpoujade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/01 12:26:28 by lpoujade          #+#    #+#             */
/*   Updated: 2016/06/10 13:35:45 by lpoujade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static inline void	adjcols(t_files *list, int count)
{
	t_files *a;

	a = list;
	while (a && count)
	{
		adjust_cols(a->fields_len, list->fields_len);
		adjust_cols(list->fields_len, a->fields_len);
		if (!(a = (t_files*)a->next) && count--)
			a = list;
	}
}

/*
** Loop on **argv list,
** fill opts with options
** for files : loads file infos and insert file in a list, sorted as requested
** for folder: same, but get folder's files in a list
*/

t_files				*p_args(char const **av, int ac, t_params *opts)
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
			a = (t_files*)fts_new(ft_strdup(av[ap]), *opts);
			ft_lstinsert(a->fcount ? (t_list**)&list : (t_list**)&false_subs,
					(t_list*)a, *opts & TIME_SORT ? &fts_timecmp : &fts_strcmp);
		}
	ft_lstappend((t_list*)false_subs, (t_list*)list);
	false_subs ? list = false_subs : 0;
	adjcols(list, ac);
	return (list);
}

static inline void	rev_output(t_files *list, t_params opts)
{
	list = rev_print_slist(lastnode(list));
	rev_recurse_out(list, opts);
	while ((list = (t_files*)list->prev))
		rev_recurse_out(list, opts);
}

int					main(int ac, char const **av)
{
	t_params	opts;
	t_files		*list;

	opts = 0;
	list = NULL;
	if (!(list = p_args(av, ac, &opts)))
		list = (t_files*)fts_new(ft_strdup("."), opts);
	while (list)
	{
		if (list->fcount && !list->subfiles)
			unfold(list, opts);
		else if (!list->fcount && !(opts & REV_SORT))
			st_fputstr(list->details, list->fields_len);
		if (list->subfiles && !(opts & REV_SORT))
			recurse_out(list, opts);
		if (!list->next)
			break ;
		list = (t_files*)list->next;
	}
	if (opts & REV_SORT)
		rev_output(list, opts);
	ft_lstiter((t_list*)list, &fts_delnode);
	return (EXIT_SUCCESS);
}
