/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   src/lsdir.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpoujade <lpoujade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/11 14:08:04 by lpoujade          #+#    #+#             */
/*   Updated: 2016/02/11 17:23:29 by lpoujade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_fileinfo		*lsdir(char *dname)
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
			finfo->infos = ft_strdup(dfile->d_name);
			finfo->next = malloc(sizeof(t_fileinfo));
			finfo->next->prev = finfo;
			finfo = finfo->next;
		}
		if ((closedir(ddir) != 0))
			perror("ls: ");
		ft_memdel((void *)&dstat);
	}
	else
		perror(ft_strjoin("ls: ", dname));
	return (finfo);
}

void	lsprint(t_fileinfo *flist)
{
	while (flist)
	{
		if (!flist->infos)
			flist = flist->prev;
		ft_putstr(flist->infos); ft_putchar('\t');
		flist = flist->prev;
	}
}
