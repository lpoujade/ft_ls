/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   src/subfuncs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpoujade <lpoujade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/26 15:55:39 by lpoujade          #+#    #+#             */
/*   Updated: 2016/03/26 17:06:33 by lpoujade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int			fts_foldstrcmp(t_list *s1, t_list *s2)
{
	int				i;
	unsigned char	*a;
	unsigned char	*b;

	i = 0;
	a = (unsigned char*)((t_fileinfo*)s1)->infos;
	b = (unsigned char*)((t_fileinfo*)s2)->infos;
	while (a[i] == b[i] && a[i] && b[i])
		i++;
	return (a[i] - b[i]);
}

int			fts_strcmp(t_list *s1, t_list *s2)
{
	int				i;
	unsigned char	*a;
	unsigned char	*b;

	a = (unsigned char*)((t_fileinfo*)s1)->infos;
	b = (unsigned char*)((t_fileinfo*)s2)->infos;
	i = 0;
	while (a[i] == b[i] && a[i] && b[i])
		i++;
	return (a[i] - b[i]);
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
