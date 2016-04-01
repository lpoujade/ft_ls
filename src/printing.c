/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   src/printing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpoujade <lpoujade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/20 18:46:23 by lpoujade          #+#    #+#             */
/*   Updated: 2016/03/30 13:57:30 by lpoujade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static char	print_typef_lastchar(mode_t f)
{
	char c;

	c = ' ';
	if (S_ISLNK(f))
		c = '@';
	else if (S_ISREG(f) && f & S_IXUSR)
		c = '*';
	else if (S_ISFIFO(f))
		c = '|';
	else if (S_ISSOCK(f))
		c = '=';
	else if (S_ISDIR(f))
		c = '/';
	return (c);
}

static char	file_mode(mode_t f)
{
	char c;

	c = '?';
	if (S_ISLNK(f))
		c = 'l';
	if (S_ISREG(f))
		c = '-';
	if (S_ISFIFO(f))
		c = 'p';
	if (S_ISCHR(f))
		c = 'c';
	if (S_ISBLK(f))
		c = 'b';
	if (S_ISSOCK(f))
		c = 's';
	if (S_ISDIR(f))
		c = 'd';
	return (c);
}

static char	*ft_print_fmode(mode_t details)
{
	char	*rights;
	int		i;

	i = 0;
	rights = (char*)malloc(10);
	rights[0] = details & S_IRUSR ? 'r' : '-';
	rights[1] = details & S_IWUSR ? 'w' : '-';
	if (details & S_IXUSR && details & S_ISUID)
		rights[2] = 's';
	else if (details & S_ISUID)
		rights[2] = 'S';
	else if (details & S_IXUSR)
		rights[2] = 'x';
	else
		rights[2] = '-';
	rights[3] = details & S_IRGRP ? 'r' : '-';
	rights[4] = details & S_IWGRP ? 'w' : '-';
	if (details & S_IXGRP && details & S_ISGID)
		rights[5] = 's';
	else if (details & S_ISGID)
		rights[5] = 'S';
	else if (details & S_IXGRP)
		rights[5] = 'x';
	else
		rights[5] = '-';
	rights[6] = details & S_IROTH ? 'r' : '-';
	rights[7] = details & S_IWOTH ? 'w' : '-';
	rights[8] = details & S_IXGRP ? 'x' : '-';
	rights[9] = 0;
	return (rights);
}

int			pfile_infos(char **buff, char *fname, t_params opts)
{
	struct stat		details;
	char			*infos;
	struct passwd	*ui;
	struct group	*gi;
	char			*slash;

	(void)buff;
	if (lstat(fname, &details) == -1)
		return (-1);
	if (!(opts & FULL_NAMES) && (slash = ft_strrchr(fname, '/')))
		slash = (*(slash + 1)) ? slash + 1 : fname;
	else
		slash = fname;
	if (!(opts & 0x01))
	{
		*buff = ft_strdup(slash);
		return (details.st_size);
		if (opts & ADD_FTYPE)
			print_typef_lastchar(details.st_mode);
	}
	ui = getpwuid(details.st_uid);
	gi = getgrgid(details.st_gid);
	infos = (char *)malloc(55 + ft_strlen(fname));
	*infos = file_mode(details.st_mode);
	ft_strcat(infos, ft_print_fmode(details.st_mode));
	ft_strcat(infos, "  ");
	ft_strcat(infos, ft_itoa(details.st_nlink));
	ft_strcat(infos, "  ");
	ft_strcat(infos, ui->pw_name ? ui->pw_name : ft_itoa(ui->pw_uid));
	ft_strcat(infos, "  ");
	ft_strcat(infos, gi->gr_name ? gi->gr_name : ft_itoa(gi->gr_gid));
	ft_strcat(infos, "  ");
	ft_strcat(infos, ft_itoa(details.st_size));
	ft_strcat(infos, details.st_size >= 100 ? "  " : "    ");
	ft_strncat(infos, ctime(&details.st_mtime) + 4, 12);
	ft_strcat(infos, "  ");
	ft_strcat(infos, slash);
	ft_strcat(infos, "\n\0");
	*buff = ft_strdup(infos);
	return (details.st_size);
}

/*
static void	putfsize(off_t bytes, int hreadable)
{
	if (!hreadable)
		ft_putnbr(bytes);
	else
	{
		if (bytes < 1024)
			ft_putstr(ft_strjoin(ft_itoa(bytes), "B"));
		else if (bytes < 1024 * 1024)
		{
			while ((bytes /= 1024) > 1024)
				;
			ft_putnbr(bytes);
			ft_putchar('K');
		}
	}
}
*/
