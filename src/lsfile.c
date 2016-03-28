/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lsfile.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpoujade <lpoujade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/11 14:08:04 by lpoujade          #+#    #+#             */
/*   Updated: 2016/03/28 13:38:56 by lpoujade         ###   ########.fr       */
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
	struct stat		stated_file;
	int				first_time;
	int				nfile;

	tmp = *fflist;
	first_time = -1;
	while (tmp)
	{
		if (!tmp->fcount && lstat(tmp->infos, &stated_file) != -1)
		{
			if (!(opts & ONLY_FOLD) && first_time > -1)
				pfile_infos(stated_file, tmp->infos, opts);
			if (stated_file.st_mode & S_IFDIR && (opts & 0x04 || c > 0))
				nfile = fts_lstinsert_l(*fflist,
						fold_list(tmp->infos, opts), &fts_strcmp);
			(nfile != -1 && (!tmp->next) && !(opts & 0x01)) ? ft_putchar('\n') : 0;
			ft_bzero((void**)&stated_file, sizeof(struct stat));
		}
		else if (!tmp->fcount && first_time > -1)
			perror(ft_strjoin("ls: lstat: ", tmp->infos));
		if (tmp->fcount)
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

	fflist = NULL;
	if ((ddir = opendir(dname)))
	{
		ft_lstinsert((t_list**)&fflist, fts_new(dname), &fts_strcmp);
		fflist->fcount = 4577;
		while ((dfile = readdir(ddir)))
			if (*dfile->d_name != '.' || opts & 0x08 ||
					(opts & 0x20 && (ft_strcmp(dfile->d_name, ".")
									&& ft_strcmp(dfile->d_name, ".."))))
				ft_lstinsert((t_list**)&fflist, fts_new(ft_strjoin(dname,
								ft_strjoin("/", dfile->d_name))), opts & TIME_SORT ? &ftime_cmp : &fts_strcmp);
		if ((closedir(ddir) != 0))
			perror("ls: closedir: ");
	}
	else
		perror(ft_strjoin("ls: opendir: ", dname));
	return (fflist);
}
