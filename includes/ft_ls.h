/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   includes/ft_ls.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpoujade <lpoujade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/11 14:08:46 by lpoujade          #+#    #+#             */
/*   Updated: 2016/03/26 17:55:55 by lpoujade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

# include <sys/stat.h>
# include <sys/types.h>
# include <uuid/uuid.h>
# include <sys/xattr.h>
# include <grp.h>
# include <pwd.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <dirent.h>
# include <time.h>
# include <errno.h>
# include "libft.h"

# define LONG_FORMAT	0x01
# define REV_SORT		0x02
# define RECURSIVE		0x04
# define ALL			0x08
# define TIME_SORT		0x10
# define ALMOST_ALL		0x20
# define HUMAN_READ		0x40
# define HIDE_OWNER		0x80
# define ONLY_FOLD		0x100

typedef int				t_params;

typedef struct			s_fileinfo
{
	t_list				*next;
	t_list				*prev;
	char				*infos;
	int					fcount;
}						t_fileinfo;

void			eval(t_fileinfo **fflist, t_params opts, int c);
t_fileinfo		*fold_list(char *dname, t_params opts);
void			pfile_infos(struct stat details, char *fname, t_params opts);

t_params		parse_args(char *av);

void			ls_out(t_fileinfo *flist, t_params opts);
void			ftls_del(void *no);
t_list			*fts_new(char *fname);
int				fts_strcmp(t_list *s1, t_list *s2);
int				fts_lstinsert_l(t_fileinfo *flist, t_fileinfo *lnew,
		int (*f)(t_list *, t_list *));
int				fts_foldstrcmp(t_list *s1, t_list *s2);
#endif
