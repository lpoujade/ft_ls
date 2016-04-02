/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   src/printing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpoujade <lpoujade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/20 18:46:23 by lpoujade          #+#    #+#             */
/*   Updated: 2016/04/02 14:38:52 by lpoujade         ###   ########.fr       */
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
	int		i;

	i = 0;
	rights = (char*)malloc(11);
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
	rights[10] = 0;
	return (rights);
}

static inline int	ndigits(int a)
{
	int c;

	c = 0;
	if (!a)
		return (1);
	while (a)
	{
		a /= 10;
		c++;
	}
	return (c);
}

int			pfile_infos(t_fileinfo *node, char *fname, t_params opts)
{
	struct stat		details;
	struct passwd	*ui;
	struct group	*gi;
	char			*slash;

	if (lstat(fname, &details) == -1)
	{
		perror(ft_strjoin("ls: lstat: ", fname));
		return (-1);
	}
	node->s_size = ndigits(details.st_size);
	node->fcount = S_ISDIR(details.st_mode) ? -1 : 0;
	if (!(opts & FULL_NAMES) && (slash = ft_strrchr(fname, '/')))
		slash = (*(slash + 1)) ? slash + 1 : fname;
	else
		slash = fname;
	node->details = (char **)malloc(8);
	if (!(opts & 0x01))
	{
		if (opts & ADD_FTYPE)
		{
			node->details[0] = ft_strnew(ft_strlen(slash) + 1);
			ft_strcpy(node->details[0], slash);
			node->details[0][ft_strlen(slash)] = print_typef_lastchar(details.st_mode);
		}
		else
			node->details[0] = slash;
		return (details.st_blocks);
	}
	ui = getpwuid(details.st_uid);
	gi = getgrgid(details.st_gid);
	node->details[0] = ft_strdup(ft_print_fmode(details.st_mode));
	node->details[1] = ft_strdup(ft_itoa(details.st_nlink));
	node->details[2] = ft_strdup(ui->pw_name ? ui->pw_name : ft_itoa(ui->pw_uid));
	node->details[3] = ft_strdup(gi->gr_name ? gi->gr_name : ft_itoa(gi->gr_gid));
	if (S_ISCHR(details.st_mode) || S_ISBLK(details.st_mode))
		node->details[4] = ft_strjoin(ft_itoa(major(details.st_rdev)), ft_strjoin(", ", ft_itoa(minor(details.st_rdev))));
	else
		node->details[4] = ft_itoa(details.st_size);
	node->details[5] = ft_strnew(12);
	ft_strncpy(node->details[5], ctime(&details.st_mtime) + 4, 12);
	if (opts & ADD_FTYPE)
	{
		node->details[6] = ft_strnew(ft_strlen(slash) + 1);
		ft_strcpy(node->details[6], slash);
		node->details[6][ft_strlen(slash)] = print_typef_lastchar(details.st_mode);
	}
	else
		node->details[6] = slash;
	node->details[7] = (char*)0;
	return (details.st_blocks);
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
