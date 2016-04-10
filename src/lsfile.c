/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lsfile.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpoujade <lpoujade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/11 14:08:04 by lpoujade          #+#    #+#             */
/*   Updated: 2016/04/10 15:32:31 by lpoujade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void				eval(t_fileinfo **fflist, t_params opts, int c)
{
	t_fileinfo		*tmp;
	int				first_time;
	int				*s_local;
	t_fileinfo		*todel;

	tmp = *fflist;
	first_time = c;
	s_local = NULL;
	while (tmp)
	{
		todel = tmp;
		!tmp->details && !tmp->fcount ? pfile_infos(tmp, tmp->infos, opts) : 0;
		if ((opts & RECURSIVE || c > 0) && tmp->fcount == -1)
			ft_lstappend((t_list*)tmp, (t_list*)fold_list(tmp->infos, opts));
		if (tmp->fcount > 0 || tmp->fcount == -2)
		{
			pdir_infos(tmp, (first_time != c + 1), opts);
			s_local = tmp->s_len;
		}
		if (!tmp->fcount || c < 0)
		{
			st_fputstr(tmp->details, s_local);
			ft_putchar(!(opts & LONG_FORMAT) ? '\t' : '\n');
		}
		tmp = (t_fileinfo *)tmp->next;
		free(todel->details);
		free(todel);
		--c;
	}
	!(opts & LONG_FORMAT) ? ft_putchar('\n') : 0;
}

static inline void	adjust_cols(int *final, int *act)
{
	int c;

	c = 6;
	while (c + 1)
	{
		if (final[c] < act[c])
			final[c] = act[c];
		c--;
	}
}

static t_fileinfo	*prevdir(t_fileinfo *act, int dirs)
{
	t_fileinfo *tmp;

	tmp = act;
	while (dirs && tmp->next)
	{
		if (tmp->fcount == -1)
			--dirs;
		tmp = (t_fileinfo*)tmp->next;
	}
	return (tmp);
}

t_fileinfo			*fold_list(char *dname, t_params opts)
{
	DIR					*ddir;
	struct dirent		*dfile;
	t_fileinfo			*fflist;
	t_fileinfo			*node;
	int					*fsizes;
	int					*s_local;
	int					dir_in;

	fflist = NULL;
	dir_in = 1;
	node = (t_fileinfo*)fts_new(dname); fflist = node;
	while (dir_in)
	{
		//ft_putstr("unfolding "); ft_putstr(dname);
		dir_in = 0;
		if (!(ddir = opendir(dname)))
			perror(ft_strjoin("ls: opendir: ", dname));
		fsizes = &node->fcount;
		s_local = node->s_len;
		while ((dfile = readdir(ddir)))
			if ((opts & ALMOST_ALL || *dfile->d_name != '.') &&
					(opts & ALL || (ft_strcmp(dfile->d_name, ".") &&
									ft_strcmp(dfile->d_name, ".."))))
			{
				node = (t_fileinfo *)ft_lstinsert((t_list**)&fflist,
						fts_new(ft_strjoin(dname, ft_strjoin("/", dfile->d_name))),
						((opts & TIME_SORT) ? &ftime_cmp : &fts_strcmp));
				*fsizes += pfile_infos(node, node->infos, opts);
				adjust_cols(s_local, node->s_len);
				node->fcount == -1 ? dir_in++ : 0;
			}
		if ((closedir(ddir) != 0))
			perror("ls: closedir: ");
		!*fsizes ? *fsizes = -2 : 0;
		if (opts & RECURSIVE && dir_in)
		{
			if (prevdir(fflist, dir_in) && prevdir(fflist, dir_in)->fcount == -1)
				dname = prevdir(fflist, dir_in)->infos;
			else
				break ;
			node->next = fts_new(dname);
			node = (t_fileinfo*)node->next;
			dir_in--;
		}
		opts & RECURSIVE ? 0 : (dir_in = 0);
	}
	//ft_putendl("fold list return this : "); ls_out(fflist, opts); ft_putendl("\n----------------");
	return (fflist);
}
