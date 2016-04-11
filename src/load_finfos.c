/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   src/load_finfos.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpoujade <lpoujade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/08 14:25:57 by lpoujade          #+#    #+#             */
/*   Updated: 2016/04/11 12:07:43 by lpoujade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static inline char	file_mode(mode_t f, int end)
{
	char c;

	c = '?';
	if (S_ISLNK(f))
		c = end ? '@' : 'l';
	else if (S_ISREG(f))
		c = '-';
	else if (S_ISFIFO(f))
		c = end ? '|' : 'p';
	else if (S_ISSOCK(f))
		c = end ? '=' : 's';
	else if (S_ISDIR(f))
		c = end ? '/' : 'd';
	else if (S_ISCHR(f) && !end)
		c = 'c';
	else if (S_ISBLK(f) && !end)
		c = 'b';
	if (end && c == '-' && S_IXUSR & f)
		c = '*';
	else if (!(S_IXUSR & f) && end)
		c = ' ';
	return (c);
}

static inline char	*ft_print_fmode(mode_t details)
{
	char	*rights;

	rights = ft_strnew(10);
	rights[0] = file_mode(details, 0);
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

char				*fts_date(time_t const *clock)
{
	char 	*date;
	char	*t_buf;
	time_t	act;

	date = ft_strnew(13);
	t_buf = ctime(clock);
	date = ft_strncpy(date, t_buf + 4, 12);
	if ((time(&act) - *clock) >= 13042800 || act < *clock)
		ft_strncpy(date + 7, t_buf + 19, 5);
	return (date);
}

int					pfile_infos(t_fileinfo *node, char *fname, t_params opts)
{
	struct stat		stated;
	char			*slash;
	char			*tmp;

	if (!(opts & FULL_NAMES) && (slash = ft_strrchr(fname, '/')))
		slash = (*(slash + 1)) ? slash + 1 : fname;
	else
		slash = fname;
	node->details = (char **)malloc(sizeof(char *) * 8);
	if ((lstat(fname, &stated) == -1))
	{
		//perror(ft_strjoin("ls: lstat: ", fname));
		node->details[0] = ft_strjoin("ls: ", ft_strjoin(fname, ft_strjoin(": ", strerror(errno))));
		node->details[1] = NULL;
		return (0);
	}
	node->fcount = S_ISDIR(stated.st_mode) && !node->fcount ? -1 : 0;
	if (!(opts & 0x01))
	{
		node->details[0] = slash;
		node->details[1] = NULL;
		return (stated.st_blocks);
	}
	if (opts & ADD_FTYPE && slash)
	{
		tmp = slash;
		slash = ft_strnew(ft_strlen(slash) + 1);
		ft_memmove(slash, tmp, ft_strlen(tmp));
		slash[ft_strlen(tmp)] = file_mode(stated.st_mode, 1);
	}
	return (s_pfileinfo(stated, node, slash));
}

int					s_pfileinfo(struct stat stated, t_fileinfo *node, char *slash)
{
	struct passwd	*ui;
	struct group	*gi;
	char			*tmp;

	ui = getpwuid(stated.st_uid);
	gi = getgrgid(stated.st_gid);
	node->s_len[2] = ft_strlen((node->details[2]
				= ui->pw_name ? ft_strdup(ui->pw_name) : ft_itoa(ui->pw_uid)));
	node->s_len[3] = ft_strlen((node->details[3]
				= gi->gr_name ? ft_strdup(gi->gr_name) : ft_itoa(gi->gr_gid)));
	node->s_len[0] = ft_strlen((node->details[0]
				= ft_print_fmode(stated.st_mode)));
	node->s_len[1] = ft_strlen((node->details[1] = ft_itoa(stated.st_nlink)));
	node->s_len[4] = ft_strlen((node->details[4]
				= (S_ISCHR(stated.st_mode) || S_ISBLK(stated.st_mode)) ?
		ft_strjoin(ft_itoa(major(stated.st_rdev)),
				ft_strjoin(", ", ft_itoa(minor(stated.st_rdev))))
		: ft_itoa(stated.st_size)));
	if (S_ISLNK(stated.st_mode))
	{
		tmp = ft_strnew(255);
		tmp[readlink(node->infos, tmp, 255)] = 0;
		slash = ft_strjoin(slash, ft_strjoin(" -> ", tmp));
	}
	node->s_len[5] = ft_strlen((node->details[5] = fts_date(&stated.st_mtime)));
	node->details[6] = slash;
	node->details[7] = NULL;
	return (stated.st_blocks);
}
