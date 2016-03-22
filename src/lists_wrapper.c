/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   src/lists.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpoujade <lpoujade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/12 17:50:35 by lpoujade          #+#    #+#             */
/*   Updated: 2016/03/22 21:20:16 by lpoujade         ###   ########.fr       */
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

	new = malloc(sizeof(t_fileinfo));
	new->infos = fname;
	new->next = NULL;
	new->prev = NULL;
	return ((t_list *)new);
}

void		fflist_add(t_fileinfo **file_list, char *fname)
{
	t_fileinfo	*new;

	if (!(new = malloc(sizeof(t_fileinfo))))
	{
		perror(ft_strjoin("ls: ", fname));
		exit(3);
	}
	new->infos = fname;
	new->prev = NULL;
	//new->prev = (t_list*)new;
	new->next = NULL;
	if (!*file_list)
		*file_list = new;
	else
		ft_lstinsert((t_list**)file_list, (t_list*)new, &fts_strcmp);
}

void		ls_out(t_fileinfo *flist, t_params opts)
{
	(void)opts;
	while (flist)
	{
		ft_putstr(flist->infos);
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
