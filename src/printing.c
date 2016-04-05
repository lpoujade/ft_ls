/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   src/printing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpoujade <lpoujade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/20 18:46:23 by lpoujade          #+#    #+#             */
/*   Updated: 2016/04/05 14:37:46 by lpoujade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static inline char	print_typef_lastchar(mode_t f)
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

static inline char	file_mode(mode_t f)
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

static inline char	*ft_print_fmode(mode_t details)
{
	char	*rights;

	rights = ft_strnew(10);
	rights[0] = file_mode(details);
	rights[1] = details & S_IRUSR ? 'r' : '-';
	rights[2] = details & S_IWUSR ? 'w' : '-';
	if (details & S_IXUSR && details & S_ISUID)
		rights[3] = 's';
	else if (details & S_ISUID)
		rights[3] = 'S';
	else if (details & S_IXUSR)
		rights[3] = 'x';
	else
		rights[3] = '-';
	rights[4] = details & S_IRGRP ? 'r' : '-';
	rights[5] = details & S_IWGRP ? 'w' : '-';
	if (details & S_IXGRP && details & S_ISGID)
		rights[6] = 's';
	else if (details & S_ISGID)
		rights[6] = 'S';
	else if (details & S_IXGRP)
		rights[6] = 'x';
	else
		rights[6] = '-';
	rights[7] = details & S_IROTH ? 'r' : '-';
	rights[8] = details & S_IWOTH ? 'w' : '-';
	rights[9] = details & S_IXGRP ? 'x' : '-';
	return (rights);
}

char				*fts_date(char *act) /* to replace with f(time_t --) */
{
	char *date;

	ret = ft_strnew(24);
	ret = date;
	ft_strncpy(node->details[5], ctime(&stated.st_mtime) + 4, 12);
}

int					pfile_infos(t_fileinfo *node, char *fname, t_params opts)
{
	struct stat		stated;
	struct passwd	*ui;
	struct group	*gi;
	char			*slash;
	char			*tmp;

	if (lstat(fname, &stated) == -1)
	{
		perror(ft_strjoin("ls: lstat: ", fname));
		exit (3);
	}
	node->s_len = ft_getndigits(stated.st_size);
	node->fcount = S_ISDIR(stated.st_mode) && !node->fcount ? -1 : 0;
	if (!(opts & FULL_NAMES) && (slash = ft_strrchr(fname, '/')))
		slash = (*(slash + 1)) ? slash + 1 : fname;
	else
		slash = fname;
	if (opts & ADD_FTYPE && slash)
	{
		tmp = slash;
		slash = ft_strnew(ft_strlen(slash) + 1);
		ft_memmove(slash, tmp, ft_strlen(tmp));
		slash[ft_strlen(tmp)] = print_typef_lastchar(stated.st_mode);
	}
	node->details = (char **)malloc(sizeof(char *) * 8);
	if (!(opts & 0x01))
	{
		node->details[0] = slash;
		node->details[1] = NULL;
		return (stated.st_blocks);
	}
	ui = getpwuid(stated.st_uid);
	gi = getgrgid(stated.st_gid);
	node->details[0] = ft_strdup(ft_print_fmode(stated.st_mode));
	node->details[1] = ft_strdup(ft_itoa(stated.st_nlink));
	node->details[2] = ft_strdup(ui->pw_name ? ui->pw_name : ft_itoa(ui->pw_uid));
	node->details[3] = ft_strdup(gi->gr_name ? gi->gr_name : ft_itoa(gi->gr_gid));
	node->details[4] = (S_ISCHR(stated.st_mode) || S_ISBLK(stated.st_mode)) ?
		ft_strjoin(ft_itoa(major(stated.st_rdev)),
				ft_strjoin(", ", ft_itoa(minor(stated.st_rdev))))
		: ft_itoa(stated.st_size);
	if (S_ISLNK(stated.st_mode))
	{
		tmp = ft_strnew(255);
		tmp[readlink(fname, tmp, 255)] = 0;
		slash = ft_strjoin(slash, ft_strjoin(" -> ", tmp));
	}
	node->details[5] = fts_filedate(ctime(&stated.st_mtime));
	node->details[6] = slash;
	node->details[7] = NULL;
	return (stated.st_blocks);
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
