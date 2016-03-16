/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   src/lsdir.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpoujade <lpoujade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/11 14:08:04 by lpoujade          #+#    #+#             */
/*   Updated: 2016/03/16 12:09:44 by lpoujade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_fileinfo	*eval(t_fileinfo **fflist, t_params opts)
{
	t_fileinfo		*tmp;
	struct stat		stated_file;

	tmp = *fflist;
	while (tmp)
	{
		lstat(tmp->infos, &stated_file);
		if (stated_file.st_mode & S_IFDIR)
			fold_list(fflist, tmp->infos, opts);
		else
			if (opts & 0x01)
				parse_file_infos(&tmp->infos, &stated_file);
		ft_bzero((void**)&stated_file, sizeof(struct stat));
		tmp = tmp->next;
		if (tmp && (*tmp->infos != '.' || opts & 0x08 || // -a
					(opts & 0x20 && (ft_strcmp(tmp->infos, ".") // -A
									&& ft_strcmp(tmp->infos, "..")))))
			(tmp) ? tmp = tmp->next : (void)0;
	}
	return (*fflist);
}

void			fold_list(t_fileinfo **fflist, char *dname, t_params opts)
{
	DIR					*ddir;
	struct dirent		*dfile;

	errno = 0;
	if ((ddir = opendir(dname)))
	{
		while ((dfile = readdir(ddir))) // error ?
			if (*dfile->d_name != '.' || opts & 0x08 || // -a
					(opts & 0x20 && (ft_strcmp(dfile->d_name, ".") // -A
									&& ft_strcmp(dfile->d_name, ".."))))
				fflist_add_end(fflist, ft_strjoin(dname, ft_strjoin("/", dfile->d_name)));
		if ((closedir(ddir) != 0))
			perror("ls: ");
	}
	else
		perror(ft_strjoin("ls: ", dname));
}

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

void		parse_file_infos(char **fname, struct stat *details)
{
	char			*infos;
	struct passwd	*user_infos;
	struct group	*gr_infos;

	infos = ft_strnew(55 + ft_strlen(*fname));

	user_infos = getpwuid(details->st_uid);
	gr_infos = getgrgid(details->st_gid);
	*infos = file_mode(details->st_mode);
	ft_strcat(infos, "(riights)"); ft_strcat(infos, "  ");
	ft_strcat(infos, "  N "); ft_strcat(infos, "   ");
	ft_strcat(infos, user_infos->pw_name); ft_strcat(infos, "   ");
	ft_strcat(infos, gr_infos->gr_name); ft_strcat(infos, "   ");
	ft_strcat(infos, "\n");
	ft_strdel(fname);
	*fname = infos;
}
