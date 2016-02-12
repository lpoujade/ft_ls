/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   src/lsdir.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpoujade <lpoujade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/11 14:08:04 by lpoujade          #+#    #+#             */
/*   Updated: 2016/02/12 16:53:19 by lpoujade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_fileinfo		*lsdir(char *dname, t_params opts)
{
	DIR					*ddir = NULL;
	struct dirent		*dfile = NULL;
	struct stat			*dstat = NULL;
	t_fileinfo			*finfo;

	finfo = malloc(sizeof(t_fileinfo));
	finfo->prev = NULL;
	if ((ddir = opendir(dname)))
	{
		dstat = malloc(sizeof(struct stat));
		while ((dfile = readdir(ddir)))
		{
			stat(dfile->d_name, dstat); // error
			if (*dfile->d_name != '.' || opts & 1000)
			{
				finfo->infos = ft_strdup(dfile->d_name);
				if ((opts & 1))
					finfo->infos = ft_strjoin(finfo->infos, "\n");
				finfo->next = malloc(sizeof(t_fileinfo));
				finfo->next->prev = finfo;
				finfo = finfo->next;
			}
		}
		if ((closedir(ddir) != 0))
			perror("ls: ");
		ft_memdel((void *)&dstat);
	}
	else
		perror(ft_strjoin("ls: ", dname));
	return (finfo);
}

void	ls_out(t_fileinfo *flist)
{
	while (flist)
	{
		if (!flist->infos)
		{
			flist = flist->prev;
			ft_memdel((void **)&flist->next);
		}
		ft_putstr(flist->infos); ft_putchar('\t');
		ft_memdel((void **)&flist->next);
	}
}
