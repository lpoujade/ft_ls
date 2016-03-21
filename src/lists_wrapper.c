/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   src/lists.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpoujade <lpoujade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/12 17:50:35 by lpoujade          #+#    #+#             */
/*   Updated: 2016/03/21 15:54:12 by lpoujade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static int	ft_void_strcmp(void *s1, void *s2)
{
	return (ft_strcmp(s1, s2));
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
	new->next = NULL;
	if (!*file_list)
		*file_list = new;
	else
		fts_lstinsert((t_list**)file_list, (t_list*)new, &ft_void_strcmp);
		//method ? node_insert_strcmp(file_list, new) : node_add(file_list, new);
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
