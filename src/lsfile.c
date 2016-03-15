/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   src/lsdir.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpoujade <lpoujade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/11 14:08:04 by lpoujade          #+#    #+#             */
/*   Updated: 2016/03/15 12:42:40 by lpoujade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

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
		tmp = tmp->next;
		ft_bzero((void**)&stated_file, sizeof(struct stat));
	}
	return (*fflist);
}

void		parse_file_infos(char **fname, struct stat *details)
{
	char			*infos;
	struct passwd	*user_infos;
	struct group	*gr_infos;

	infos = malloc(55 + ft_strlen(*fname));
	ft_memset((void*)infos, ' ', 54 + ft_strlen(*fname));
	infos[55 + ft_strlen(*fname)] = 0;

	user_infos = getpwuid(details->st_uid);
	gr_infos = getgrgid(details->st_gid);

	if (details->st_mode & S_IFDIR)
		*infos = 'd';
	else if (details->st_mode & S_IFREG)
		*infos = '-';
	ft_strcat(infos, "(rights)");
	ft_strcat(infos + 8, ft_strjoin(user_infos->pw_name, gr_infos->gr_name));
	ft_putendl(infos);
	ft_strdel(fname);
	*fname = infos;
}
