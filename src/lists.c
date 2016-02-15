/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   src/lists.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpoujade <lpoujade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/12 17:50:35 by lpoujade          #+#    #+#             */
/*   Updated: 2016/02/14 19:15:59 by lpoujade         ###   ########.fr       */
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
