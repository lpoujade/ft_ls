/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lists.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpoujade <lpoujade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/01 12:47:58 by lpoujade          #+#    #+#             */
/*   Updated: 2016/06/09 11:49:31 by lpoujade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_list		*fts_new(char const *fname, t_params opts)
{
	t_files	*new;

	if (!(new = (t_files*)malloc(sizeof(t_files))))
	{
		perror(ft_strjoin("ls: ", fname));
		exit(3);
	}
	new->next = NULL;
	new->prev = NULL;
	new->name = (char*)fname;
	new->details = NULL;
	new->fcount = 0;
	new->subfiles = NULL;
	new->path = NULL;
	new->fields_len[7] = pfile_infos(new, new->name, opts);
	if (new->fcount)
	{
		new->path = ft_strnew(ft_strlen(new->name) + 1);
		ft_strcat(new->path, new->name);
		ft_strcat(new->path, "/");
	}
	return ((t_list *)new);
}

void		fts_delnode(t_list *onode)
{
	t_files *node;
	int		i;

	i = 0;
	node = (t_files*)onode;
	if (node->subfiles)
		ft_lstiter((t_list*)node->subfiles, &fts_delnode);
	if (node)
	{
		while (node->details[i])
		{
			if (*node->details[i])
				free(node->details[i]);
			i++;
		}
		if (node->path)
			free(node->path);
		free(node);
	}
	node = NULL;
}

int			fts_strcmp(t_list *s1, t_list *s2)
{
	int				i;
	unsigned char	*a;
	unsigned char	*b;

	a = (unsigned char*)((t_files*)s1)->name;
	b = (unsigned char*)((t_files*)s2)->name;
	i = 0;
	while (a[i] && b[i] && a[i] == b[i])
		i++;
	return (a[i] - b[i]);
}

int			fts_timecmp(t_list *of1, t_list *of2)
{
	t_files f1;
	t_files f2;

	f1 = *(t_files*)of1;
	f2 = *(t_files*)of2;
	if ((double)f1.stmp.tv_sec < (double)f2.stmp.tv_sec)
		return (1);
	else if ((double)f1.stmp.tv_sec > (double)f2.stmp.tv_sec)
		return (-1);
	else if ((double)f1.stmp.tv_nsec < (double)f2.stmp.tv_nsec)
		return (1);
	else if ((double)f1.stmp.tv_nsec > (double)f2.stmp.tv_nsec)
		return (-1);
	else
		return (fts_strcmp(of1, of2));
	return (0);
}

t_files		*lastnode(t_files *list)
{
	t_files	*ln;

	ln = list;
	while (ln && ln->next)
		ln = (t_files*)ln->next;
	return (ln);
}
