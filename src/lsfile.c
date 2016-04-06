/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lsfile.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpoujade <lpoujade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/11 14:08:04 by lpoujade          #+#    #+#             */
/*   Updated: 2016/04/06 22:12:14 by lpoujade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static inline void	st_fputstr(char **details, int *nbrmax)
{
	int c;
	int	step;

	c = 0;
	while (*details && c <= 7)
	{
		if (**details)
		{
			step = nbrmax[c] - ft_strlen(*details);
			if (nbrmax[c] < 20)
				while (step--)
					write(1, " ", 1);
			ft_putstr(*details);
			ft_putchar(' ');
		}
		c++;
		details++;
	}
}

static inline void	pdir_infos(t_fileinfo *dir,
		int first_time, t_params opts)
{
	if (first_time)
	{
		ft_putstr(opts & LONG_FORMAT ? "\n" : "\n\n");
		ft_putstr(dir->infos);
		ft_putstr(":\n");
	}
	if (opts & LONG_FORMAT && dir->fcount > 0)
	{
		ft_putstr("total ");
		ft_putnbr(dir->fcount);
		ft_putchar('\n');
	}
}

static t_list		*nextdir(t_fileinfo *act)
{
	t_fileinfo	*tmp;

	tmp = act;
	while (tmp->next)
		tmp = (t_fileinfo*)tmp->next;
	return ((t_list*)tmp);
}

void				eval(t_fileinfo **fflist, t_params opts, int c)
{
	t_fileinfo		*tmp;
	int				first_time;
	int				*s_local;
	int				s_default[7] = {10, 10, 10, 10, 10, 10, 10};
	t_fileinfo		*todel;

	tmp = *fflist;
	first_time = c;
	s_local = NULL;
	while (tmp)
	{
		todel = tmp;
		!tmp->details && !tmp->fcount ? pfile_infos(tmp, tmp->infos, opts) : 0;
		if ((opts & RECURSIVE || c > 0) && tmp->fcount == -1)
			ft_lstinsert_list(nextdir(tmp), (t_list*)fold_list(tmp->infos, opts), &fts_strcmp);
		if (tmp->fcount > 0 || tmp->fcount == -2)
		{
			pdir_infos(tmp, (first_time != c + 1), opts);
			s_local = tmp->s_len;
		}
		else if (!tmp->fcount || c < 0)
		{
			st_fputstr(tmp->details, s_local ?: s_default);
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

t_fileinfo			*fold_list(char *dname, t_params opts)
{
	DIR					*ddir;
	struct dirent		*dfile;
	t_fileinfo			*fflist;
	t_fileinfo			*node;
	int					*fsizes;
	int					*s_local;

	fflist = NULL;
	if (!(ddir = opendir(dname)))
		perror(ft_strjoin("ls: opendir: ", dname));
	ft_lstinsert((t_list**)&fflist, fts_new(dname), &fts_strcmp);
	fsizes = &fflist->fcount;
	s_local = fflist->s_len;
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
		}
	if ((closedir(ddir) != 0))
		perror("ls: closedir: ");
	!*fsizes ? *fsizes = -2 : 0;
	return (fflist);
}
