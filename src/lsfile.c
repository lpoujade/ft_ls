/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lsfile.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpoujade <lpoujade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/01 12:39:08 by lpoujade          #+#    #+#             */
/*   Updated: 2016/06/06 17:49:10 by lpoujade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void				adjust_cols(int *final, int *act)
{
	int c;

	c = 6;
	while (c + 1)
	{
		if (final[c] < act[c])
			final[c] = act[c];
		c--;
	}
}

/*
** Open a folder then read files in
** return a list of files,
** with info requested in opts
*/

static inline DIR	*myopen(char *dname)
{
	DIR		*ddir;

	if ((ddir = opendir(dname)))
		return (ddir);
	else
	{
		perror(ft_strjoin("ls: ", dname));
		return (NULL);
	}
}

t_files				*unfold(t_files *fold, t_params opts)
{
	DIR				*ddir;
	struct dirent	*dfile;
	t_list			*act;

	if (!(ddir = myopen(fold->name)))
		return (NULL);
	while ((dfile = readdir(ddir)))
		if ((opts & (ALMOST_ALL | ALL) || *dfile->d_name != '.') &&
			(opts & ALL || (ft_strcmp(dfile->d_name, ".") &&
							ft_strcmp(dfile->d_name, ".."))))
		{
			act = ft_lstinsert((t_list**)&fold->subfiles,
					fts_new(ft_strjoin(fold->path, dfile->d_name), opts),
					opts & TIME_SORT ? &fts_timecmp : &fts_strcmp);
			adjust_cols(fold->fields_len, ((t_files*)act)->fields_len);
			fold->fcount += ((t_files*)act)->fields_len[7];
			if (opts & RECURSIVE && ((t_files*)act)->fcount &&
					(ft_strcmp(dfile->d_name, ".") &&
					ft_strcmp(dfile->d_name, "..")))
				unfold((t_files*)act, opts);
		}
	if (closedir(ddir) == -1)
		perror(ft_strjoin("ls: ", fold->name));
	return (fold->subfiles);
}
