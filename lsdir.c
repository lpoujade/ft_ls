/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lsdir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpoujade <lpoujade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/03 13:04:52 by lpoujade          #+#    #+#             */
/*   Updated: 2016/02/03 19:28:09 by lpoujade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/stat.h>
#include <sys/types.h>
#include <uuid/uuid.h>
#include <sys/xattr.h>
#include <pwd.h>
#include <stdlib.h>
#include <stdio.h>
#include <dirent.h>
#include <time.h>
#include "libft.h"

int		main(int ac, char **av)
{
	if (ac == 1)
		return (1);

	DIR	*ddir = NULL;
	struct dirent	*dfile = NULL;

	if ((ddir = opendir(av[1])))
	{
		struct	stat			*dstat = malloc(sizeof(struct stat));
		struct	passwd		*dpwd = NULL;
		while ((dfile = readdir(ddir)))
		{
			stat(dfile->d_name, dstat); // error
			dpwd = getpwuid(dstat->st_uid);
			ft_putnbr(dstat->st_size);ft_putchar('\t');
			ft_putstr(dpwd->pw_name);ft_putchar(':');
			ft_putnbr(dstat->st_gid);ft_putchar('\t');
			ft_putstr(ctime(&dstat->st_birthtime));ft_putchar('\r');
			ft_putendl(dfile->d_name);
		}
		if ((closedir(ddir) != 0))
			perror("ls: ");
		ft_memdel((void *)&dstat);
	}
	else
		perror(ft_strjoin("ls: ", av[1]));
	return (0);
}
