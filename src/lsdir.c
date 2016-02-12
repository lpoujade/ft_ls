/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   src/lsdir.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpoujade <lpoujade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/11 14:08:04 by lpoujade          #+#    #+#             */
/*   Updated: 2016/02/12 22:16:22 by lpoujade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_fileinfo		*lsdir(char *dname, t_params opts)
{
	DIR					*ddir = NULL;
	struct dirent		*dfile = NULL;
	struct stat			*dstat = NULL;
	t_fileinfo			*o_finfo = NULL;
	t_fileinfo			*finfo = NULL;

	if ((ddir = opendir(dname)))
	{
		finfo = malloc(sizeof(t_fileinfo));
		o_finfo = finfo;
		finfo->next = NULL; finfo->prev = NULL;
		dstat = malloc(sizeof(struct stat)); // error
		while ((dfile = readdir(ddir)))
		{
			stat(dfile->d_name, dstat); // error
			if (*dfile->d_name != '.' || opts&1000)
			{
				finfo->infos = ft_strdup(dfile->d_name);

				if ((opts & 1)) // -l
					finfo->infos = ft_strjoin(finfo->infos, "\n");

				finfo->next = malloc(sizeof(t_fileinfo));
				finfo->next->prev = finfo;
				finfo = finfo->next;
				// void node
			}
		}
		finfo->next = o_finfo;
		o_finfo->prev = finfo;
		if ((closedir(ddir) != 0))
			perror("ls: ");
		ft_memdel((void *)&dstat);
	}
	else
		perror(ft_strjoin("ls: ", dname));
	return (finfo);
}

void	ls_out(t_fileinfo *flist, int rev)
{
	t_fileinfo *mark;

	mark = flist;
	flist = (rev) ? flist->prev : flist->next;
	if (rev)
		ft_strdel(&flist->next->infos);
	else
		ft_strdel(&flist->prev->infos);
	while (flist != mark)
	{
		ft_putstr(flist->infos);
		flist = (rev) ? flist->prev : flist->next;
		if (flist)
		{
			if (rev)
				ft_strdel(&flist->next->infos);
			else
				ft_strdel(&flist->prev->infos);
		}
	}
}
