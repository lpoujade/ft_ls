/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lsfile.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpoujade <lpoujade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/11 14:08:04 by lpoujade          #+#    #+#             */
/*   Updated: 2016/03/25 19:51:16 by lpoujade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void			eval(t_fileinfo **fflist, t_params opts, int c)
{
	t_fileinfo		*tmp;
	struct stat		stated_file;

	tmp = *fflist;
	while (tmp)
	{
		if (!tmp->fcount && lstat(tmp->infos, &stated_file) != -1)
		{
			if (!(opts & ONLY_FOLD) && tmp->prev && tmp->prev->prev)
				pfile_infos(stated_file, tmp->infos, opts);
			if (stated_file.st_mode & S_IFDIR && (opts & 0x04 || c > 0))
				fts_lstinsert_l(tmp, fold_list(tmp->infos, opts), &fts_strcmp);
			((!tmp->next) && !(opts & 0x01)) ? ft_putchar('\n') : 0;
			ft_bzero((void**)&stated_file, sizeof(struct stat));
		}
		else if (!tmp->fcount)
			perror(ft_strjoin("(lsfile.c:lstat)ls: ", tmp->infos));

		if (tmp->fcount)
		{
			ft_putchar('\n');
			ft_putstr(tmp->infos);
			ft_putendl(":");
			if (opts & LONG_FORMAT)
			{
				ft_putstr("total ");
				ft_putnbr(tmp->fcount ? tmp->fcount : 0);
				ft_putchar('\n');
			}
		}
		tmp = (t_fileinfo*)tmp->next;
		c--;
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
		fts_lstadd_nfold(&fflist, dname);
		fflist->fcount = 2;
		while ((dfile = readdir(ddir)))
			if (*dfile->d_name != '.' || opts & 0x08 ||
					(opts & 0x20 && (ft_strcmp(dfile->d_name, ".")
									&& ft_strcmp(dfile->d_name, ".."))))
				fts_lstadd_nfold(&fflist,
						ft_strjoin(dname, ft_strjoin("/", dfile->d_name)));
		if ((closedir(ddir) != 0))
			perror("(lsfile.c:closedir)ls: ");
	}
	else
		perror(ft_strjoin("(lsfile.c:opendir)ls: ", dname));
	return ((fflist ? fflist : (t_fileinfo*)fts_new("")));
}
