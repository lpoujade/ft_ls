/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   src/lists.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpoujade <lpoujade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/12 17:50:35 by lpoujade          #+#    #+#             */
/*   Updated: 2016/02/13 14:35:27 by lpoujade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void		lst_newn(char *infos, unsigned int atime, t_fileinfo *onode)
{
	t_fileinfo	*new;
	t_fileinfo	*o;

	new = malloc(sizeof(t_fileinfo));
	new->infos = ft_strdup(infos);
	new->epoch = atime;
	if (!onode)
	{
		new->next = new;
		new->prev = new;
	}
	else
	{
		o = onode->prev;
		if (atime)
			while (onode != o)
			{
				if (atime >= onode->epoch)
				{
					onode->next->prev = new;
					new->next = onode->next;
					onode->next = new;
					new->prev = onode;
					break ;
				}
				onode = onode->next;
			}
		else
		{
			onode->next->prev = new;
			new->next = onode->next;
			onode->next = new;
			new->prev = onode;
		}
	}

}
