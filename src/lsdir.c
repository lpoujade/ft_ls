/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   src/lsdir.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpoujade <lpoujade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/11 14:08:04 by lpoujade          #+#    #+#             */
/*   Updated: 2016/02/11 14:35:33 by lpoujade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int		lsdir(char *dirname, t_params opts)
{
	DIR				*ddir = NULL;
	struct dirent	*dfile = NULL;
	struct	stat		*dstat = malloc(sizeof(struct stat));
	struct	passwd		*dpwd = NULL;

	if ((ddir = opendir(dirname)))
	{
		while ((dfile = readdir(ddir)))
		{
			// if (opt->l) -> save all infos / else save dfile->filename
			stat(dfile->d_name, dstat); // error
			dpwd = getpwuid(dstat->st_uid);
			ft_putnbr(dstat->st_size);ft_putchar('\t');
			ft_putstr(dpwd->pw_name);ft_putchar(':');
			ft_putnbr(dstat->st_gid);ft_putchar('\t');
			ft_putnbr(dstat->st_birthtime);ft_putchar(' ');
			ft_putendl(dfile->d_name);
			// if (opt->r && file == dir) -> add dirname to dirs name's list; will be used after
		}
		if ((closedir(ddir) != 0))
			perror("ls: ");
		ft_memdel((void *)&dstat);
	}
	else
		perror(ft_strjoin("ls: ", av[1]));
	return (0);
}
