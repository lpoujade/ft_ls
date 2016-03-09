/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   src/lists.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpoujade <lpoujade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/12 17:50:35 by lpoujade          #+#    #+#             */
/*   Updated: 2016/03/09 13:03:04 by lpoujade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

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

/*
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
		
	}
	else
	{
		if (!(tmp = malloc(sizeof(t_fileinfo))))
		{
			perror(ft_strjoin("ls: ", fname));
			exit(3);
		}
		ft_strcpy(tmp->infos, fname);
		while (*fname > (char)(*file_list)->infos && (*file_list)->next) // TODO: better sorting
			*file_list = (*file_list)->next;
		tmp->next = *file_list;
		tmp->prev = (*file_list)->prev;
		((*file_list)->prev)->next = tmp;
		(*file_list)->prev = tmp;
	}
}
