/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   src/lists.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpoujade <lpoujade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/12 17:50:35 by lpoujade          #+#    #+#             */
/*   Updated: 2016/03/17 22:38:13 by lpoujade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void		fflist_add(t_fileinfo **file_list, char *fname) // TODO sorting method
															// default alphabetically
{
	t_fileinfo	*new;
	t_fileinfo	*tmp;

	if (!*file_list)
	{
		if (!(*file_list = malloc(sizeof(t_fileinfo))))
		{
			perror(ft_strjoin("ls: ", fname));
			exit(3);
		}
		(*file_list)->prev = NULL;
		(*file_list)->next = NULL;
		(*file_list)->infos = fname;
	}
	else
	{
		if (!(new = malloc(sizeof(t_fileinfo))))
		{
			perror(ft_strjoin("ls: ", fname));
			exit(3);
		}
		tmp = (*file_list);
		new->infos = fname;
		while (ft_strcmp(fname, tmp->infos) > 0 && tmp->next)
			tmp = tmp->next;
		if (ft_strcmp(fname, tmp->infos) > 0)
		{
			new->next = tmp->next;
			tmp->next = new;
			new->prev = tmp;
		}
		else
		{
			tmp->prev->next = new;
			new->next = tmp;
			new->prev = tmp->prev;
			tmp->prev = new;
		}
	}
}

void		ls_out(t_fileinfo *flist, t_params opts) // TODO output format
{
	(void)opts;
	while (flist)
	{
		ft_putstr(flist->infos); ft_putchar('\t');
		flist = flist->next;
	}
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
