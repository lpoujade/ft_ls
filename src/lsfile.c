/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lsfile.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpoujade <lpoujade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/11 14:08:04 by lpoujade          #+#    #+#             */
/*   Updated: 2016/03/23 20:53:43 by lpoujade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void			eval(t_fileinfo **fflist, t_params opts, int c)
{
	t_fileinfo		*tmp;
	struct stat		stated_file;

	tmp = *fflist;
	while (tmp)
	{
		if (tmp->tot && tmp->prev)
		{
			ft_putchar('\n');
			ft_putstr(tmp->infos);
			ft_putendl(":");
			if (opts & LONG_FORMAT)
			{
				ft_putstr("total ");
				ft_putnbr(tmp->tot);
				ft_putchar('\n');
			}
		}
		else
		{
			if (lstat(tmp->infos, &stated_file) == -1)
			{
				perror(ft_strjoin("ls: ", tmp->infos));
				exit(3);
			}
			if (stated_file.st_mode & S_IFDIR && (opts & 0x04 || c > 0))
				ft_lstinsert_list((t_list*)*fflist, (t_list*)fold_list(tmp->infos, opts), &fts_strcmp);
			if ((c > 0 || !(opts & ONLY_FOLD)) && tmp->tot!= -1)
				print_file_infos(stated_file, tmp->infos, opts);
			((tmp && !tmp->next) && !(opts & 0x01)) ? ft_putchar('\n') : 0;
			ft_bzero((void**)&stated_file, sizeof(struct stat));
		}
		tmp = (t_fileinfo*)tmp->next;
		c--;
	}
}

t_fileinfo		*fold_list(char *dname, t_params opts)
{
	DIR					*ddir;
	struct dirent		*dfile;
	t_fileinfo			*fflist;
	int					*tot;

	fflist = NULL;
	if ((ddir = opendir(dname)))
	{
		fflist = (t_fileinfo*)fts_new(dname);
		tot = &(*fflist).tot;
		while ((dfile = readdir(ddir)))
			if (*dfile->d_name != '.' || opts & 0x08 ||
					(opts & 0x20 && (ft_strcmp(dfile->d_name, ".")
									&& ft_strcmp(dfile->d_name, ".."))))
			{
				fts_lstadd_nfold(&fflist,
						ft_strjoin(dname, ft_strjoin("/", dfile->d_name)));
				(*tot)++;
			}
		if (!*tot)
			*tot = -1;
		if ((closedir(ddir) != 0))
			perror("ls: ");
	}
	else
		perror(ft_strjoin("ls: ", dname));
	return ((fflist ? fflist : (t_fileinfo*)fts_new("")));
}
