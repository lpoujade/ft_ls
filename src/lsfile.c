/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lsfile.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpoujade <lpoujade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/11 14:08:04 by lpoujade          #+#    #+#             */
/*   Updated: 2016/03/19 18:12:52 by lpoujade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_fileinfo	*eval(t_fileinfo **fflist, t_params opts, int c)
{
	t_fileinfo		*tmp;
	struct stat		stated_file;

	tmp = *fflist;
	while (tmp)
	{
		if (lstat(tmp->infos, &stated_file) == -1)
		{
			perror(ft_strjoin("ls: ", tmp->infos));
			exit (3);
		}
		if (stated_file.st_mode & S_IFDIR && (c || opts & 0x04) &&
				ft_strcmp(tmp->infos, "..") && ft_strcmp(tmp->infos, "."))
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
		c--;
	}
	return (*fflist);
}

void		fold_list(t_fileinfo **fflist, char *dname, t_params opts)
{
	DIR					*ddir;
	struct dirent		*dfile;

	errno = 0;
	if ((ddir = opendir(dname)))
	{
		while ((dfile = readdir(ddir)))
			if (*dfile->d_name != '.' || opts & 0x08 ||
					(opts & 0x20 && (ft_strcmp(dfile->d_name, ".")
									&& ft_strcmp(dfile->d_name, ".."))))
				fflist_add(fflist,
						ft_strjoin(dname, ft_strjoin("/", dfile->d_name)), 1);
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

static void	ft_print_fmode(mode_t details)
{
	details & S_IRUSR ? ft_putchar('r') : ft_putchar('-');
	details & S_IWUSR ? ft_putchar('w') : ft_putchar('-');
	if (details & S_IXUSR && details & S_ISUID)
		ft_putchar ('s');
	else if (!details & S_IXUSR && details & S_ISUID)
		ft_putchar('S');
	else if (details & S_IXUSR & !details & S_ISUID)
		ft_putchar('x');
	else
		ft_putchar('-');
	details & S_IRGRP ? ft_putchar('r') : ft_putchar('-');
	details & S_IWGRP ? ft_putchar('w') : ft_putchar('-');
	if (details & S_IXGRP && details & S_ISUID)
		ft_putchar ('s');
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
	ft_print_fmode(details.st_mode);
	ft_putnbr(details.st_nlink);
	ft_putstr("  ");
	ft_putstr(ft_strjoin(user_infos->pw_name, "  "));
	ft_putstr(ft_strjoin(gr_infos->gr_name, "  "));
	ft_putnbr(details.st_size);
	ft_putstr("\t");
	ft_putstr(ft_strjoin(last_access, "  "));
	ft_putendl(ft_strrchr(fname, '/') + 1);
}

/*
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
	ft_strcat(infos, ctime(&details->st_atime));
	infos[ft_strlen(infos) - 1] = 0; ft_strcat(infos, "   ");
	ft_strcat(infos, *fname);
	ft_strcat(infos, "\n");
	ft_strdel(fname);
	*fname = infos;
}
*/
