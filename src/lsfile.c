/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lsfile.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpoujade <lpoujade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/11 14:08:04 by lpoujade          #+#    #+#             */
/*   Updated: 2016/04/02 13:34:19 by lpoujade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void		pdir_infos(t_fileinfo *dir,
		int first_time, t_params opts)
{
	if (first_time)
	{
		ft_putstr(opts & LONG_FORMAT ? "\n" : "\n\n");
		ft_putstr(dir->infos);
		ft_putstr(":\n");
	}
	if (opts & LONG_FORMAT)
	{
		ft_putstr("total ");
		ft_putnbr(dir->fcount ? dir->fcount : 0);
		ft_putchar('\n');
	}
}

void			eval(t_fileinfo **fflist, t_params opts, int c)
{
	t_fileinfo		*tmp;
	int				first_time;

	tmp = *fflist;
	first_time = c;
	while (tmp)
	{
		!tmp->details && !tmp->fcount ? pfile_infos(tmp, tmp->infos, opts) : 0;
		if ((opts & RECURSIVE || c > 0) && tmp->fcount == -1)
			fts_lstinsert_l(tmp, fold_list(tmp->infos, opts), &fts_strcmp);
		if (tmp->fcount > 0)
			pdir_infos(tmp, (first_time != c + 1), opts);
		else if (!tmp->fcount || c < 0)
		{
			ft_putstr(tmp->details);
			!(opts & LONG_FORMAT) ? ft_putchar('\t') : 0;
		}
		tmp = (t_fileinfo *)tmp->next;
		//tmp && tmp->prev ? free(tmp->prev) : 0;
		--c;
	}
	!(opts & LONG_FORMAT) ? ft_putchar('\n') : 0;
/*
	while (tmp)
	{
		if ((!tmp->details))
			if (pfile_infos(&tmp->details, tmp->infos, opts) == -1)
				exit (errno);
		if (*tmp->details == 'd' && !tmp->fcount && (opts & 0x04 || c > 0))
			fts_lstinsert_l(tmp,
					fold_list(tmp->infos, opts), &fts_strcmp);
		else if (*tmp->details == 'd' && tmp->fcount)
			pdir_infos(tmp, first_time, opts);
		else
			ft_putstr(tmp->details);
		!(opts & LONG_FORMAT) ? ft_putchar('\t') : 0;
		(!tmp->next && !(opts & 0x01)) ? ft_putchar('\n') : 0;
		tmp = (t_fileinfo*)tmp->next;
		c--;
		first_time++;
	}
	*/
}

t_fileinfo		*fold_list(char *dname, t_params opts)
{
	DIR					*ddir;
	struct dirent		*dfile;
	t_fileinfo			*fflist;
	t_fileinfo			*node;
	int					*fsizes;

	fflist = NULL;
	if (!(ddir = opendir(dname)))
		perror(ft_strjoin("ls: opendir: ", dname));
	ft_lstinsert((t_list**)&fflist, fts_new(dname), &fts_strcmp);
	fsizes = &fflist->fcount;
	while ((dfile = readdir(ddir)))
		if ((opts & ALMOST_ALL || *dfile->d_name != '.') &&
				(opts & 0x20 || (ft_strcmp(dfile->d_name, ".") && ft_strcmp(dfile->d_name, ".."))))
		{
			node = ((t_fileinfo*)ft_lstinsert((t_list**)&fflist,
						fts_new(ft_strjoin(dname, ft_strjoin("/", dfile->d_name))),
						opts & TIME_SORT ? &ftime_cmp : &fts_strcmp));
			*fsizes += pfile_infos(node, ft_strjoin(dname, ft_strjoin("/", dfile->d_name)), opts);
		}
	if ((closedir(ddir) != 0))
		perror("ls: closedir: ");
	return (fflist);
}
