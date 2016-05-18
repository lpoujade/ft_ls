/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lsfile.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpoujade <lpoujade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/11 14:08:04 by lpoujade          #+#    #+#             */
/*   Updated: 2016/05/18 13:42:55 by lpoujade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static inline t_list *nextdir(t_fileinfo *onode)
{
	t_fileinfo *node;

	node = onode;
	while (node->next && (node->fcount <= 0 || node->fcount == -2))
		node = (t_fileinfo *)node->next;
	return ((t_list *)node);
}

t_fileinfo			*eval(t_fileinfo **fflist, t_params opts, int c)
{
	t_fileinfo		*tmp;
	t_list			*ndir;
	int				*s_local;
	short			first;

	first = 1;
	tmp = *fflist;
	s_local = NULL;
	ndir = (t_list*)tmp;
	while (tmp)
	{
		!tmp->details && !tmp->fcount ? pfile_infos(tmp, tmp->infos, opts) : 0;
		if ((opts & RECURSIVE || c > 0) && tmp->fcount == -1)
		{
			ndir = nextdir(tmp);
			ft_lstinsert_list((t_list**)ndir, (t_list*)fold_list(tmp->infos, opts),
					&fts_strcmp);
		}
		if ((tmp->fcount > 0 || tmp->fcount == -2) && !(opts & REV_SORT))
		{
			pdir_infos(tmp, &first, opts);
			s_local = tmp->s_len;
		}
		else if ((!tmp->fcount || c < 0) && !(opts & REV_SORT))
		{
			st_fputstr(tmp->details, s_local);
			if (tmp->next || opts & LONG_FORMAT)
				ft_putchar('\n');
		}
		if ((tmp = (t_fileinfo *)tmp->next) && !(opts & REV_SORT))
			fts_delnode((t_fileinfo*)tmp->prev);
		--c;
	}
	return (opts & REV_SORT ? *fflist : NULL);
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

static inline char	*fname_join(char *dir, char *fname)
{
	char	*ret;

	ret = ft_strnew(ft_strlen(dir) + ft_strlen(fname) + 1);
	ft_strcat(ret, dir);
	ft_strcat(ret + ft_strlen(dir), "/");
	ft_strcat(ret + ft_strlen(dir) + 1, fname);
	return (ret);
}

t_fileinfo			*fold_list(char *dname, t_params opts)
{
	DIR					*ddir;
	struct dirent		*dfile;
	t_fileinfo			*fflist;
	t_fileinfo			*node;
	int					*fsizes;
	int					*s_local;

	node = (t_fileinfo*)fts_new(dname);
	fflist = node;
	fsizes = &node->fcount;
	if (!(ddir = opendir(dname)))
	{
		node->next = fts_new("NOP");
		((t_fileinfo*)node->next)->details = (char**)malloc(2);
		((t_fileinfo*)node->next)->details[0] = ft_strjoin(dname, ft_strjoin(": ", strerror(errno)));
		((t_fileinfo*)node->next)->details[1] = NULL;
	}
	else
	{
		s_local = node->s_len;
		while ((dfile = readdir(ddir)))
			if ((opts & ALMOST_ALL || *dfile->d_name != '.' || opts & ALL) &&
					(opts & ALL || (ft_strcmp(dfile->d_name, ".") &&
									ft_strcmp(dfile->d_name, ".."))))
			{
				if (*(node = (t_fileinfo *)ft_lstinsert(&fflist->next,
								fts_new(fname_join(dname, dfile->d_name)),
								((opts & 0x10) ? &ftime_cmp : &fts_strcmp)))->infos)
				{
					*fsizes += pfile_infos(node, node->infos, opts);
					adjust_cols(s_local, node->s_len);
				}
			}
		if ((closedir(ddir) != 0))
			perror("ls: closedir: ");
	}
	!*fsizes ? *fsizes = -2 : 0;
	return (fflist);
}

/*
t_fileinfo		*unfold_list(t_fileinfo *flist, t_params opts)
{
	DIR					*ddir;
	struct dirent		*dfile;
	t_fileinfo			*tmp;

	while (tmp)
	{
		rrrrrr
	}
}
*/
