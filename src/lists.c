/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   src/lists.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpoujade <lpoujade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/12 17:50:35 by lpoujade          #+#    #+#             */
/*   Updated: 2016/03/21 23:46:06 by lpoujade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void		node_insert_strcmp(t_fileinfo **fflist, t_fileinfo *node)
{
	t_fileinfo	*tmp;
	int			comp;

	tmp = (*fflist);
	while ((comp = ft_strcmp(node->infos, tmp->infos)) > 0 && tmp->next)
		tmp = tmp->next;
	if (comp > 0)
	{
		if (tmp->next)
			tmp->next->prev = node;
		node->next = tmp->next;
		tmp->next = node;
		node->prev = tmp;
	}
	else
	{
		node->next = tmp;
		node->prev = tmp->prev;
		if (tmp->prev)
			tmp->prev->next = node;
		else
			*fflist = node;
		tmp->prev = node;
	}
}

void	node_add(t_fileinfo **fflist, t_fileinfo *new)
{
	t_fileinfo *tmp;

	tmp = *fflist;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
	//new->prev = tmp; ??
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
		//method ? node_insert_strcmp(file_list, new) : node_add(file_list, new);
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
