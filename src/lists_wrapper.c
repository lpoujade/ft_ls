/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lists_wrapper.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpoujade <lpoujade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/12 17:50:35 by lpoujade          #+#    #+#             */
/*   Updated: 2016/05/19 21:41:06 by lpoujade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void		add_list(t_fileinfo *nlist, t_fileinfo *act_list, t_params opts)
{
	(void)opts;
	t_fileinfo	*end_nlist;

	end_nlist = nlist;
	while (end_nlist->next)
		end_nlist = (t_fileinfo*)end_nlist->next;
	while (act_list->next && (act_list->fcount <= 0 && act_list->fcount != -2))
		act_list = (t_fileinfo*)act_list->next;

	act_list->prev = (t_list*)act_list;
	end_nlist->next = act_list->next;
	act_list->next = (t_list*)nlist;
	return ;
}

t_list		*fts_new(char *fname)
{
	t_fileinfo	*new;

	if (!(new = (t_fileinfo*)malloc(sizeof(t_fileinfo))))
	{
		perror(ft_strjoin("ls: ", fname));
		exit(3);
	}
	new->infos = fname;
	new->next = NULL;
	new->prev = NULL;
	new->fcount = 0;
	new->details = NULL;
	new->s_len[6] = 0;
	new->s_len[5] = 0;
	new->s_len[4] = 0;
	new->s_len[3] = 0;
	new->s_len[2] = 0;
	new->s_len[1] = 0;
	new->s_len[0] = 0;
	return ((t_list *)new);
}

void		fts_delnode(t_fileinfo *node)
{
	return ;
	if (node)
	{
		if (node->details)
			free(node->details);
		free(node);
	}
	node = NULL;
}
