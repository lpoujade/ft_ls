/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   src/printing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpoujade <lpoujade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/20 18:46:23 by lpoujade          #+#    #+#             */
/*   Updated: 2016/03/20 18:51:05 by lpoujade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static char	file_mode(mode_t f)
{
	char c;

	if (f & S_IFREG)
		c = '-';
	else if (f & S_IFDIR)
		c = 'd';
	else if (f & S_IFIFO)
		c = 'p';
	else if (f & S_IFCHR)
		c = 'c';
	else if (f & S_IFBLK)
		c = 'b';
	else if (f & S_IFLNK)
		c = 'l';
	else if (f & S_IFSOCK)
		c = 's';
	else
		c = '?';
	return (c);
}

static void	ft_print_fmode(mode_t details)
{
	details & S_IRUSR ? ft_putchar('r') : ft_putchar('-');
	details & S_IWUSR ? ft_putchar('w') : ft_putchar('-');
	if (details & S_IXUSR && details & S_ISUID)
		ft_putchar('s');
	else if (!details & S_IXUSR && details & S_ISUID)
		ft_putchar('S');
	else if (details & S_IXUSR & !details & S_ISUID)
		ft_putchar('x');
	else
		ft_putchar('-');
	details & S_IRGRP ? ft_putchar('r') : ft_putchar('-');
	details & S_IWGRP ? ft_putchar('w') : ft_putchar('-');
	if (details & S_IXGRP && details & S_ISUID)
		ft_putchar('s');
	else if (!details & S_IXGRP && details & S_ISUID)
		ft_putchar('S');
	else if (details & S_IXGRP & details & S_ISUID)
		ft_putchar('x');
	else
		ft_putchar('-');
	details & S_IROTH ? ft_putchar('r') : ft_putchar('-');
	details & S_IWOTH ? ft_putchar('w') : ft_putchar('-');
	details & S_IXGRP ? ft_putchar('x') : ft_putchar('-');
	ft_putstr("  ");
}

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

void		print_file_infos(struct stat details, char *fname, t_params opts)
{
	struct passwd	*user_infos;
	struct group	*gr_infos;
	char			*last_access;
	char			*slash;

	slash = ft_strrchr(fname, '/');
	if (!(opts & 0x01))
	{
		ft_putstr(slash ? slash + 1 : fname);
		ft_putchar('\t');
		return ;
	}
	last_access = ctime(&details.st_atime);
	last_access[24] = 0;
	!(opts & 0x80) ? user_infos = getpwuid(details.st_uid) : (void)0;
	gr_infos = getgrgid(details.st_gid);
	ft_putchar(file_mode(details.st_mode));
	ft_print_fmode(details.st_mode);
	ft_putnbr(details.st_nlink);
	ft_putstr("  ");
	!(opts & 0x80) ? ft_putstr(ft_strjoin(user_infos->pw_name, "  ")) : (void)0;
	ft_putstr(ft_strjoin(gr_infos->gr_name, "  "));
	putfsize(details.st_size, opts & 0x40);
	ft_putstr("\t");
	ft_putstr(ft_strjoin(last_access, "  "));
	ft_putendl(slash ? slash + 1 : fname);
}

/*
** void		parse_file_infos(char **fname, struct stat *details)
** {
** 	char			*infos;
** 	struct passwd	*user_infos;
** 	struct group	*gr_infos;
**
** 	infos = ft_strnew(55 + ft_strlen(*fname));
** 	user_infos = getpwuid(details->st_uid);
** 	gr_infos = getgrgid(details->st_gid);
** 	*infos = file_mode(details->st_mode);
** 	ft_strcat(infos, "(riights)"); ft_strcat(infos, "  ");
** 	ft_strcat(infos, ft_itoa(details->st_nlink)); ft_strcat(infos, "   ");
** 	ft_strcat(infos, user_infos->pw_name); ft_strcat(infos, "   ");
** 	ft_strcat(infos, gr_infos->gr_name); ft_strcat(infos, "   ");
** 	ft_strcat(infos, ctime(&details->st_atime));
** 	infos[ft_strlen(infos) - 1] = 0; ft_strcat(infos, "   ");
** 	ft_strcat(infos, *fname);
** 	ft_strcat(infos, "\n");
** 	ft_strdel(fname);
** 	*fname = infos;
** }
*/
