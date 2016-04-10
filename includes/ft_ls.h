/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   includes/ft_ls.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpoujade <lpoujade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/11 14:08:46 by lpoujade          #+#    #+#             */
/*   Updated: 2016/04/10 14:36:46 by lpoujade         ###   ########.fr       */
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
# define ADD_FTYPE		0x200
# define FULL_NAMES		0x400

typedef unsigned int	t_params;

typedef struct			s_fileinfo
{
	t_list				*next;
	t_list				*prev;
	char				*infos;
	char				**details;
	int					fcount;
	int					s_len[7];
}						t_fileinfo;

t_params				parse_args(char *av);
void					eval(t_fileinfo **fflist, t_params opts, int c);
t_fileinfo				*fold_list(char *dname, t_params opts);
void					ls_out(t_fileinfo *flist, t_params opts);
t_list					*fts_new(char *fname);

char					*fts_date(time_t const *clock);
int						fts_strcmp(t_list *s1, t_list *s2);
int						ftime_cmp(t_list *f1, t_list *f2);


int						pfile_infos(t_fileinfo *node, char *fname, t_params opts);
int						s_pfileinfo(struct stat stated, t_fileinfo *node, char *slash);
void					pdir_infos(t_fileinfo *dir, int first_time, t_params opts);
void					st_fputstr(char **details, int *nbrmax);
#endif
