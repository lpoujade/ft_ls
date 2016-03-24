/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lists_wrapper.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpoujade <lpoujade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/12 17:50:35 by lpoujade          #+#    #+#             */
/*   Updated: 2016/03/24 21:57:47 by lpoujade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int	fts_strcmp(t_list *s1, t_list *s2)
{
	char *a;
	char *b;
	a = ((t_fileinfo*)s1)->infos;
	b = ((t_fileinfo*)s2)->infos;
	return (ft_strcmp(a, b));
}

t_list		*fts_new(char *fname)
{
	t_fileinfo	*new;

	if (!(new = (t_fileinfo*)malloc(sizeof(t_fileinfo))))
	{
		perror(ft_strjoin("ls: ", fname));
		exit(3);
	}
	new->infos = fname;
	new->next = NULL;
	new->prev = NULL;
	new->fcount = 0;
	return ((t_list *)new);
}

int			fts_lstinsert_list(t_fileinfo *flist, t_fileinfo *lnew, int (*f)(t_list *,t_list *))
{
	if (!flist)
	{
		flist = lnew;
		return (0);
	}
	while (flist->next && !((t_fileinfo*)flist->next)->fcount)
		flist = (t_fileinfo*)flist->next;
	return (ft_lstinsert_list((t_list*)flist, (t_list*)lnew, f));
}

void		fts_lstadd_nfold(t_fileinfo **file_list, char *fname)
{
	t_fileinfo	*new;
	t_fileinfo	*tmp;

	tmp = (*file_list);
	new = (t_fileinfo*)fts_new(fname);

	ft_lstinsert((t_list**)file_list, (t_list*)new, &fts_strcmp);
}

void		ls_out(t_fileinfo *flist, t_params opts)
{
	(void)opts;
	while (flist)
	{
		ft_putstr(flist->infos);
		if (!(opts & LONG_FORMAT))
				ft_putchar('\t');
		flist = (t_fileinfo*)flist->next;
	}
}

void		ftls_del(void *no)
{
	t_fileinfo	*node;

	node = (t_fileinfo *)no;
	ft_strdel(&node->infos);
}
