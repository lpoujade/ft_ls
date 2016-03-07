/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   src/lsdir.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpoujade <lpoujade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/11 14:08:04 by lpoujade          #+#    #+#             */
/*   Updated: 2016/03/07 19:35:13 by lpoujade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_fileinfo		*lsfile(char *dname, t_params opts)
{
	DIR					*ddir = NULL;
	struct dirent		*dfile = NULL;
	struct stat			dstat;
	t_fileinfo			*finfo = NULL;

	if (lstat(dname, &dstat) == -1)
		perror(ft_strjoin("ls: ", dname));
	else if (dstat.st_mode&S_IFDIR && (ddir = opendir(dname)))
	{
		while ((dfile = readdir(ddir))) // error ?
			if (*dfile->d_name != '.' || opts&0x08 || // -a
					(opts&0x20 && (ft_strcmp(dfile->d_name, ".") // -A
								   && ft_strcmp(dfile->d_name, ".."))))
			{
				if (opts&1) // -l
					new_filelist(ft_strjoin(dfile->d_name, "\n"), 0, &finfo);
				else
					new_filelist(dfile->d_name, 0, &finfo);
			}
		if ((closedir(ddir) != 0))
			perror("ls: ");
	}
	else if (dstat.st_mode&S_IFDIR)
		perror(ft_strjoin("ls: ", dname));
	else
		new_filelist((opts&1) ? ft_strjoin(ft_itoa(dstat.st_uid), ft_strjoin(ft_itoa(dstat.st_gid), ft_strjoin(dname, "\n"))):dname, 0, &finfo);
	return (finfo);
}

void	ls_out(t_fileinfo *flist, int rev)
{
	t_fileinfo *prev;
	if (rev)
		flist = flist->prev;
	prev = flist;
	while (flist)
	{
		ft_putstr(flist->infos);
		flist = (rev) ? flist->prev : flist->next;
		prev->next = NULL;
		prev->prev = NULL;
		ft_strclr(prev->infos);
	}
}
