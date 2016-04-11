/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lsfile.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpoujade <lpoujade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/11 14:08:04 by lpoujade          #+#    #+#             */
/*   Updated: 2016/04/11 11:53:16 by lpoujade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void				eval(t_fileinfo **fflist, t_params opts, int c)
{
	t_fileinfo		*tmp;
	int				first_time;
	int				*s_local;
	t_fileinfo		*todel;

	tmp = *fflist;
	first_time = c;
	s_local = NULL;
	while (tmp)
	{
		todel = tmp;
		!tmp->details && !tmp->fcount ? pfile_infos(tmp, tmp->infos, opts) : 0;
		if ((opts & RECURSIVE || c > 0) && tmp->fcount == -1)
			ft_lstappend((t_list*)tmp, (t_list*)fold_list(tmp->infos, opts));
		if (tmp->fcount > 0 || tmp->fcount == -2)
		{
			pdir_infos(tmp, (first_time != c + 1), opts);
			s_local = tmp->s_len;
		}
		else if (!tmp->fcount || c < 0)
		{
			st_fputstr(tmp->details, s_local);
			ft_putchar(!(opts & LONG_FORMAT) ? '\t' : '\n');
		}
		tmp = (t_fileinfo *)tmp->next;
		free(todel->details);
		free(todel);
		--c;
	}
	!(opts & LONG_FORMAT) ? ft_putchar('\n') : 0;
}

static inline void	adjust_cols(int *final, int *act)
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

t_fileinfo			*fold_list(char *dname, t_params opts)
{
	DIR					*ddir;
	struct dirent		*dfile;
	t_fileinfo			*fflist;
	t_fileinfo			*node;
	int					*fsizes;
	int					*s_local;

	fflist = NULL;
	node = (t_fileinfo*)fts_new(dname); fflist = node;
	if (!(ddir = opendir(dname)))
		perror(ft_strjoin("ls: opendir: ", dname));
	fsizes = &node->fcount;
	s_local = node->s_len;
	while ((dfile = readdir(ddir)))
		if ((opts & ALMOST_ALL || *dfile->d_name != '.') &&
				(opts & ALL || (ft_strcmp(dfile->d_name, ".") &&
								ft_strcmp(dfile->d_name, ".."))))
		{
			if (*(node = (t_fileinfo *)ft_lstinsert((t_list**)&fflist,
					fts_new(ft_strjoin(dname, ft_strjoin("/", dfile->d_name))),
					((opts & TIME_SORT) ? &ftime_cmp : &fts_strcmp)))->infos)
			{
				*fsizes += pfile_infos(node, node->infos, opts);
				adjust_cols(s_local, node->s_len);
			}
		}
	if ((closedir(ddir) != 0))
		perror("ls: closedir: ");
	!*fsizes ? *fsizes = -2 : 0;
	return (fflist);
}
