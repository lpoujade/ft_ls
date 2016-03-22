/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   src/lists.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpoujade <lpoujade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/12 17:50:35 by lpoujade          #+#    #+#             */
/*   Updated: 2016/03/22 15:42:36 by lpoujade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static int	ft_void_strcmp(t_list *s1, t_list *s2)
{
	char *a;
	char *b;
	a = ((t_fileinfo*)s1)->infos;
	b = ((t_fileinfo*)s2)->infos;
	return (ft_strcmp(a, b));
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
		ft_lstinsert((t_list**)file_list, (t_list*)new, &ft_void_strcmp);
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
