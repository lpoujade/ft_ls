/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lsfile.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpoujade <lpoujade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/11 14:08:04 by lpoujade          #+#    #+#             */
/*   Updated: 2016/03/17 23:13:52 by lpoujade         ###   ########.fr       */
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
		if (stated_file.st_mode & S_IFDIR && opts & 0x04 && ft_strcmp(tmp->infos, "..") && ft_strcmp(tmp->infos, "."))
			fold_list(fflist, tmp->infos, opts);
		if (opts & 0x01)
			print_file_infos(stated_file, tmp->infos);
		else
		{
			ft_putstr(ft_strrchr(tmp->infos, '/') + 1);
			if (tmp->next)
				ft_putchar('\t');
		}
		ft_bzero((void**)&stated_file, sizeof(struct stat));
		tmp = tmp->next;
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
				fflist_add(fflist, ft_strjoin(dname, ft_strjoin("/", dfile->d_name)));
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

void		print_file_infos(struct stat details, char *fname)
{
	struct passwd	*user_infos;
	struct group	*gr_infos;
	char			*last_access;

	last_access = ctime(&details.st_atime);
	last_access[24] = 0;
	user_infos = getpwuid(details.st_uid);
	gr_infos = getgrgid(details.st_gid);
	ft_putchar(file_mode(details.st_mode));

	ft_putstr("?????????  ");
	ft_putnbr(details.st_nlink);ft_putstr("  ");
	ft_putstr(ft_strjoin(user_infos->pw_name, "  "));
	ft_putstr(ft_strjoin(gr_infos->gr_name, "  "));
	ft_putnbr(details.st_size); ft_putstr("\t");
	ft_putstr(ft_strjoin(last_access, "  "));
	ft_putendl(ft_strrchr(fname, '/') + 1);
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
	ft_strcat(infos, ft_itoa(details->st_nlink)); ft_strcat(infos, "   ");
	ft_strcat(infos, user_infos->pw_name); ft_strcat(infos, "   ");
	ft_strcat(infos, gr_infos->gr_name); ft_strcat(infos, "   ");
	ft_strcat(infos, ctime(&details->st_atime)); infos[ft_strlen(infos) - 1] = 0; ft_strcat(infos, "   ");
	ft_strcat(infos, *fname);
	ft_strcat(infos, "\n");
	ft_strdel(fname);
	*fname = infos;
}
