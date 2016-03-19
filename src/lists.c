/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   src/lists.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpoujade <lpoujade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/12 17:50:35 by lpoujade          #+#    #+#             */
/*   Updated: 2016/03/19 16:22:49 by lpoujade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void	node_insert_strcmp(t_fileinfo **fflist, t_fileinfo *node)
{
	t_fileinfo	*tmp;
	int			comp;

	tmp = (*fflist);
	while ((comp = ft_strcmp(node->infos, tmp->infos)) > 0 && tmp->next)
		tmp = tmp->next;
	if (comp > 0)
	{
		node->next = tmp->next;
		tmp->next = node;
		node->prev = tmp;
	}
	else
	{
		tmp->prev->next = node;
		node->next = tmp;
		node->prev = tmp->prev;
		tmp->prev = node;
	}
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
		node_insert_strcmp(file_list, new);
}

void		ls_out(t_fileinfo *flist, t_params opts)
{
	(void)opts;
	while (flist)
	{
		ft_putstr(flist->infos);
		ft_putchar('\t');
		flist = flist->next;
	}
}
