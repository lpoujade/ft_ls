/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   src/lsdir.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpoujade <lpoujade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/11 14:08:04 by lpoujade          #+#    #+#             */
/*   Updated: 2016/03/14 19:55:06 by lpoujade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void			fold_list(t_fileinfo **fflist, char *dname, t_params opts)
{
	DIR					*ddir = NULL;
	struct dirent		*dfile = NULL;

	errno = 0;
	if ((ddir = opendir(dname)))
	{
		while ((dfile = readdir(ddir))) // error ?
			if (*dfile->d_name != '.' || opts & 0x08 || // -a
					(opts & 0x20 && (ft_strcmp(dfile->d_name, ".") // -A
								   && ft_strcmp(dfile->d_name, ".."))))
				fflist_add_end(fflist, dfile->d_name);
		if ((closedir(ddir) != 0))
			perror("ls: ");
	}
	else
		perror(ft_strjoin("ls: ", dname));
}

t_fileinfo	*eval(t_fileinfo **fflist, t_params opts)
{
	t_fileinfo		**orig;
	struct stat		stated_file;

	orig = fflist;
	while (*fflist)
	{
		lstat((*fflist)->infos, &stated_file);
		if (stated_file.st_mode & S_IFDIR)
			fold_list(fflist, (*fflist)->infos, opts);
		*fflist = (*fflist)->next;
		ft_bzero((void**)&stated_file, sizeof(struct stat));
	}
	return (*orig);
}

void		ls_out(t_fileinfo *flist, int rev)
{
	t_fileinfo *prev;
	if (rev)
		flist = flist->prev;
	while (flist)
	{
		ft_putstr(flist->infos);
		prev = flist;
		flist = (rev) ? flist->prev : flist->next;
		prev->next = NULL;
		prev->prev = NULL;
		prev = NULL;
	}
}
