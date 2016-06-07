/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpoujade <lpoujade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/01 12:29:29 by lpoujade          #+#    #+#             */
/*   Updated: 2016/06/07 11:52:06 by lpoujade         ###   ########.fr       */
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

typedef struct		s_files
{
	t_list			*next;
	t_list			*prev;
	char			*path;
	char			*name;
	struct timespec	stmp;
	char			**details;
	int				fields_len[8];
	int				fcount;
	struct s_files	*subfiles;
}					t_files;

t_files				*p_args(char const **av, int ac, t_params *opts);
int					pfile_infos(t_files *node, char *fname, t_params opts);
int					s_pfileinfo(struct stat stated, t_files *n, char *slash);
t_list				*fts_new(char const *fname, t_params opts);
void				fts_delnode(t_list *node);
char				*fts_date(time_t const *clock);
int					fts_timecmp(t_list *f1, t_list *f2);
int					fts_strcmp(t_list *s1, t_list *s2);
t_params			parse_args(char const *av);
char				*epure_name(char *fname, t_params opts);
void				st_fputstr(char **details, int *nbrmax);
void				print_file(t_list *file);
t_files				*unfold(t_files *fold, t_params opts);
void				recurse_out(t_files *root, t_params opts);
void				rev_recurse_out(t_files *root, t_params opts);
t_files				*lastnode(t_files *list);
void				adjust_cols(int *final, int *act);
void				rev_print_slist(t_files *node);
#endif
