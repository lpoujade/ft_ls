/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lsfile.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpoujade <lpoujade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/11 14:08:04 by lpoujade          #+#    #+#             */
/*   Updated: 2016/03/21 23:44:25 by lpoujade         ###   ########.fr       */
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
//		if (!*(tmp->infos))
//		{
//			ft_putchar('\n');
//			ft_putstr(tmp->next->infos); ft_putstr(":\n");
//			tmp = tmp->next->next;
//		}
		if (lstat(tmp->infos, &stated_file) == -1)
		{
			perror(ft_strjoin("ls: ", tmp->infos));
			exit(3);
		}
		if (stated_file.st_mode & S_IFDIR && (opts & 0x04 || c > 0))
			//node_add(fflist, fold_list(tmp->infos, opts));
			node_insert_strcmp(fflist, fold_list(tmp->infos, opts));
		print_file_infos(stated_file, tmp->infos, opts); (!tmp->next && !(opts&0x01))? ft_putchar('\n') : (void)0;
		ft_bzero((void**)&stated_file, sizeof(struct stat));
		tmp = tmp->next;
		c--;
	}
	return (*fflist);
}

t_fileinfo		*fold_list(char *dname, t_params opts)
{
	DIR					*ddir;
	struct dirent		*dfile;
	t_fileinfo			*fflist;

	fflist = NULL;
	errno = 0;
	if ((ddir = opendir(dname)))
	{
		while ((dfile = readdir(ddir)))
			if (*dfile->d_name != '.' || opts & 0x08 ||
					(opts & 0x20 && (ft_strcmp(dfile->d_name, ".")
									&& ft_strcmp(dfile->d_name, ".."))))
				fflist_add(&fflist,
						ft_strjoin(dname, ft_strjoin("/", dfile->d_name)));
		if ((closedir(ddir) != 0))
			perror("ls: ");
	}
	else
		perror(ft_strjoin("ls: ", dname));
	return (fflist);
}

