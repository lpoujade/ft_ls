/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lsfile.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpoujade <lpoujade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/11 14:08:04 by lpoujade          #+#    #+#             */
/*   Updated: 2016/03/30 14:22:14 by lpoujade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void		pdir_infos(t_fileinfo *dir,
		int first_time, t_params opts, int nfile)
{
	if (first_time > 0)
	{
		ft_putchar('\n');
		ft_putstr(dir->infos);
		ft_putstr(opts & 0x01 ? " (" : ":\n");
		if (opts & LONG_FORMAT)
		{
			ft_putnbr(nfile);
			ft_putendl(" files):");
		}
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
	int				nfile;

	tmp = *fflist;
	first_time = -1;
	while (tmp)
	{
		if (!tmp->fcount)
		{
			if ((!tmp->details) && !(opts & ONLY_FOLD))
				if (pfile_infos(&tmp->details, tmp->infos, opts) == -1)
					exit (5);
			if (*tmp->details == 'd' && !tmp->fcount && (opts & 0x04 || c > 0))
				nfile = fts_lstinsert_l(*fflist,
						fold_list(tmp->infos, opts), &fts_strcmp);
			else
				ft_putstr(tmp->details);
			!(opts & LONG_FORMAT) ? ft_putchar('\t') : 0;
			(nfile != -1 && !tmp->next && !(opts & 0x01)) ? ft_putchar('\n') : 0;
		}
		else
			pdir_infos(tmp, first_time, opts, nfile);
		tmp = (t_fileinfo*)tmp->next;
		c--;
		first_time++;
	}
}

t_fileinfo		*fold_list(char *dname, t_params opts)
{
	DIR					*ddir;
	struct dirent		*dfile;
	t_fileinfo			*fflist;
	char				*details;
	int					*fsizes;

	fflist = NULL;
	if ((ddir = opendir(dname)))
	{
		ft_lstinsert((t_list**)&fflist, fts_new(dname), &fts_strcmp);
		fsizes = &fflist->fcount;
		while ((dfile = readdir(ddir)))
			if (*dfile->d_name != '.' || opts & 0x08 ||
					(opts & 0x20 && (ft_strcmp(dfile->d_name, ".")
									&& ft_strcmp(dfile->d_name, ".."))))
			{
				details = ((t_fileinfo*)ft_lstinsert((t_list**)&fflist, fts_new(ft_strjoin(dname,
								ft_strjoin("/", dfile->d_name))),
						opts & TIME_SORT ? &ftime_cmp : &fts_strcmp))->details;
				*fsizes += pfile_infos(&details, dfile->d_name, opts) / 512;
			}
		if ((closedir(ddir) != 0))
			perror("ls: closedir: ");
	}
	else
		perror(ft_strjoin("ls: opendir: ", dname));
	return (fflist);
}
