/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   src/lists.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpoujade <lpoujade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/12 17:50:35 by lpoujade          #+#    #+#             */
/*   Updated: 2016/03/15 12:06:15 by lpoujade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void		ls_out(t_fileinfo *flist, int rev)
{
	t_fileinfo *prev;

	if (rev)
		flist = flist->prev;
	while (flist)
	{
		ft_putstr(flist->infos);
		prev = flist;
		flist = (rev) ? flist->prev : flist->next;
		prev->next = NULL;
		prev->prev = NULL;
		prev = NULL;
	}
}

void		fflist_add(t_fileinfo **file_list, char *fname)
{
	t_fileinfo	*tmp;

	if (!*file_list)
	{
		if (!(*file_list = malloc(sizeof(t_fileinfo))))
		{
			perror(ft_strjoin("ls: ", fname));
			exit(3);
		}
		(*file_list)->infos = ft_strdup(fname);
		(*file_list)->prev = NULL;
		(*file_list)->next = NULL;
	}
	else
	{
		if (!(tmp = malloc(sizeof(t_fileinfo))))
		{
			perror(ft_strjoin("ls: ", fname));
			exit(3);
		}
		tmp->infos = ft_strdup(fname);
		tmp->next = *file_list;
		(*file_list)->prev = tmp;
		tmp->prev = NULL;
		*file_list = tmp;
	}
}

void		fflist_add_end(t_fileinfo **file_list, char *fname)
{
	t_fileinfo	*tmp;
	t_fileinfo	*new;

	tmp = *file_list;
	if (!(new = malloc(sizeof(t_fileinfo))))
	{
		perror(ft_strjoin("ls: ", fname));
		exit(3);
	}
	while (tmp->next)
		tmp = tmp->next;
	new->infos = ft_strdup(fname);
	new->prev = tmp;
	tmp->next = new;
	new->next = NULL;
}

/*
void		new_filelist(char *infos, unsigned int atime, t_fileinfo **onode)
{
	t_fileinfo	*new;

	new = malloc(sizeof(t_fileinfo));
	new->infos = ft_strdup(infos);
	new->epoch = atime;
	if (!*onode)
	{
		*onode = new;
		(*onode)->next = *onode;
		(*onode)->prev = *onode;
	}
	else
	{
		new->next = *onode;
		new->prev = (*onode)->prev;
		(*onode)->prev->next = new;
		(*onode)->prev = new;
	}

//	ft_putendl(ft_strjoin(" integrated ", ft_strjoin(new->infos, ft_strjoin(" between ", ft_strjoin(new->prev->infos, ft_strjoin(" and ", new->next->infos))))));
}

		if (atime)
		{
			while (*onode != mark)
			{
				if (atime >= (*onode)->epoch)
				{
					(*onode)->next->prev = new;
					new->next = (*onode)->next;
					(*onode)->next = new;
					new->prev = *onode;
				}
				*onode = (*onode)->next;
			}
		}
*/
