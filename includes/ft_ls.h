/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   includes/ft_ls.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpoujade <lpoujade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/11 14:08:46 by lpoujade          #+#    #+#             */
/*   Updated: 2016/03/22 20:39:01 by lpoujade         ###   ########.fr       */
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
# include <dirent.h>
# include <time.h>
# include <errno.h>
# include "libft.h"

typedef struct			s_fileinfo
{
	t_list				*next;
	t_list				*prev;
	char				*infos;
}						t_fileinfo;

typedef short int		t_params;

t_fileinfo		*eval(t_fileinfo **fflist, t_params opts, int c);
t_fileinfo		*fold_list(char *dname, t_params opts);
void			print_file_infos(struct stat details, char *fname, t_params opts);

t_params		parse_args(char *av);

void		fflist_add(t_fileinfo **file_list, char *fname);
void		ls_out(t_fileinfo *flist, t_params opts);
void			ls_out(t_fileinfo *flist, t_params opts);
void		ftls_del(void *no);
t_list		*fts_new(char *fname);
int	fts_strcmp(t_list *s1, t_list *s2);
#endif
