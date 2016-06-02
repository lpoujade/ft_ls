/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loadinfo.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpoujade <lpoujade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/01 12:51:26 by lpoujade          #+#    #+#             */
/*   Updated: 2016/06/02 14:47:42 by lpoujade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static inline char	file_mode(mode_t f, int end)
{
	char c;

	c = '?';
	if (S_ISLNK(f))
		c = end ? '@' : 'l';
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
	rights[3] = '-';
	rights[6] = '-';
	rights[0] = file_mode(details, 0);
	rights[1] = details & S_IRUSR ? 'r' : '-';
	rights[2] = details & S_IWUSR ? 'w' : '-';
	if (details & S_IXUSR && details & S_ISUID)
		rights[3] = 's';
	else if (details & S_ISUID)
		rights[3] = 'S';
	(details & S_IXUSR) ? rights[3] = 'x' : 0;
	rights[4] = details & S_IRGRP ? 'r' : '-';
	rights[5] = details & S_IWGRP ? 'w' : '-';
	if (details & S_IXGRP && details & S_ISGID)
		rights[6] = 's';
	else if (details & S_ISGID)
		rights[6] = 'S';
	else if (details & S_IXGRP)
		rights[6] = 'x';
	rights[7] = details & S_IROTH ? 'r' : '-';
	rights[8] = details & S_IWOTH ? 'w' : '-';
	rights[9] = details & S_IXGRP ? 'x' : '-';
	return (rights);
}

int					pfile_infos(t_files *node, char *fname, t_params opts)
{
	struct stat		stated;
	char			*slh;
	char			*tmp;

	slh = epure_name(fname, opts);
	node->details = (char **)malloc(sizeof(char *) * 8);
	node->details[1] = NULL;
	if ((lstat(fname, &stated) == -1))
	{
		node->details[0] = ft_strjoin("ls: ",
				ft_strjoin(fname, ft_strjoin(": ", strerror(errno))));
		return (0);
	}
	node->fcount = S_ISDIR(stated.st_mode) && !node->fcount ? -1 : 0;
	node->stmp = stated.st_mtimespec;
	if (opts & ADD_FTYPE)
	{
		tmp = slh;
		ft_memmove(slh = ft_strnew(ft_strlen(slh) + 1), tmp, ft_strlen(tmp));
		slh[ft_strlen(tmp)] = file_mode(stated.st_mode, 1);
	}
	if (!(opts & 0x01))
		node->details[0] = slh;
	return (opts & 0x01 ? s_pfileinfo(stated, node, slh) : stated.st_blocks);
}

inline static void	cols_iter(t_files *node)
{
	int c;

	c = 0;
	while (c < 7)
	{
		node->fields_len[c] = ft_strlen(node->details[c]);
		c++;
	}
}

int					s_pfileinfo(struct stat stated, t_files *n, char *slash)
{
	struct passwd	*ui;
	struct group	*gi;
	char			*tmp;

	ui = getpwuid(stated.st_uid);
	gi = getgrgid(stated.st_gid);
	n->details[2] = ui->pw_name ? ft_strdup(ui->pw_name) : ft_itoa(ui->pw_uid);
	n->details[3] = gi->gr_name ? ft_strdup(gi->gr_name) : ft_itoa(gi->gr_gid);
	n->details[0] = ft_print_fmode(stated.st_mode);
	n->details[1] = ft_itoa(stated.st_nlink);
	n->details[4] = (S_ISCHR(stated.st_mode) || S_ISBLK(stated.st_mode)) ?
		ft_strjoin(ft_itoa(major(stated.st_rdev)),
				ft_strjoin(", ", ft_itoa(minor(stated.st_rdev))))
		: ft_itoa(stated.st_size);
	if (S_ISLNK(stated.st_mode))
	{
		tmp = ft_strnew(255);
		tmp[readlink(n->name, tmp, 255)] = 0;
		slash = ft_strjoin(slash, ft_strjoin(" -> ", tmp));
	}
	n->details[5] = fts_date(&stated.st_mtime);
	n->details[6] = slash;
	n->details[7] = NULL;
	cols_iter(n);
	return (stated.st_blocks);
}
