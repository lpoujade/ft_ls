/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   src/lsdir.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpoujade <lpoujade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/11 14:08:04 by lpoujade          #+#    #+#             */
/*   Updated: 2016/02/13 20:05:00 by lpoujade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_fileinfo		*lsdir(char *dname, t_params opts)
{
	DIR					*ddir = NULL;
	struct dirent		*dfile = NULL;
	t_fileinfo			*finfo = NULL;

	char *to_print = NULL;

	if ((ddir = opendir(dname)))
	{
		while ((dfile = readdir(ddir))) // error ?
		{
			if (*dfile->d_name != '.' || opts&0x08) // -a
			{
				to_print = ft_strdup(dfile->d_name);
				//if (opts&1) // -l
				//	to_print = ft_strjoin(to_print, "\n");
				//if (opts&0x10) // -t time

				lst_newn(to_print, 0, &finfo);
				free(to_print);
			}
		}
		if ((closedir(ddir) != 0))
			perror("ls: ");
	}
	else if (errno == 20)
		ft_putendl("TODO: file");
	else
		perror(ft_strjoin("ls: ", dname));
	return (finfo);
}

void	ls_out(t_fileinfo *flist, int rev)
{
	t_fileinfo *prev;
	if (!rev)
		flist = flist->next;
	prev = flist;
	while (flist && 42)
	{
		ft_putstr(flist->infos);
		flist = (rev) ? flist->prev : flist->next;
		if (prev == flist)
			break ;
	}
}
