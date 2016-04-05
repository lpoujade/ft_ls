/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lists_wrapper.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpoujade <lpoujade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/12 17:50:35 by lpoujade          #+#    #+#             */
/*   Updated: 2016/04/05 13:25:29 by lpoujade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

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
	new->details = NULL;
	new->s_len = 0;
	return ((t_list *)new);
}

int			fts_lstinsert_l(t_fileinfo *flist, t_fileinfo *lnew,
								int (*f)(t_list *, t_list *))
{
	if (!flist)
	{
		flist = lnew;
		return (0);
	}
	while (flist->next && *(flist->infos))
		flist = (t_fileinfo*)flist->next;
	return (ft_lstinsert_list((t_list*)flist, (t_list*)lnew, f));
}

void		fts_del(void *no)
{
	if (no)
		free (no);
}
