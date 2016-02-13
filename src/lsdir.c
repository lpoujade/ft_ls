/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   src/lsdir.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpoujade <lpoujade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/11 14:08:04 by lpoujade          #+#    #+#             */
/*   Updated: 2016/02/13 14:31:33 by lpoujade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_fileinfo		*lsdir(char *dname, t_params opts)
{
	DIR					*ddir = NULL;
	struct dirent		*dfile = NULL;
	t_fileinfo			*finfo = NULL;

	if ((ddir = opendir(dname)))
	{
		while ((dfile = readdir(ddir)))
		{
			if (*dfile->d_name != '.' || opts&1000) // -a
			{
				//if (opts&1) // -l

				//if (opts&0x10) // -t time 
				
				lst_newn(dfile->d_name, 0, finfo);
			}
		}
		if ((closedir(ddir) != 0))
			perror("ls: ");
	}
	else
		perror(ft_strjoin("ls: ", dname));
	return (finfo);
}

void	ls_out(t_fileinfo *flist, int rev)
{
	while (flist)
	{
		ft_putstr(flist->infos);
		flist = (rev) ? flist->prev : flist->next;
	}
}
