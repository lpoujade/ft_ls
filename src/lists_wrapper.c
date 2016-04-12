/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lists_wrapper.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpoujade <lpoujade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/12 17:50:35 by lpoujade          #+#    #+#             */
/*   Updated: 2016/04/12 19:27:08 by lpoujade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

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
	if (node)
	{
		if (node->details)
			free(node->details);
		free(node);
	}
	node = NULL;
}
