/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   includes/ft_ls.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpoujade <lpoujade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/11 14:08:46 by lpoujade          #+#    #+#             */
/*   Updated: 2016/03/07 11:14:46 by lpoujade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

# include <sys/stat.h>
# include <sys/types.h>
# include <uuid/uuid.h>
# include <sys/xattr.h>
# include <pwd.h>
# include <stdlib.h>
# include <stdio.h>
# include <dirent.h>
# include <time.h>
# include <errno.h>
# include "libft.h"

typedef struct			s_fileinfo
{
	char				*infos;
	unsigned int		epoch;
	struct s_fileinfo	*next;
	struct s_fileinfo	*prev;
}						t_fileinfo;

typedef struct			s_dirlist
{
	char				*dirname;
	struct s_listdir	*next;
}						t_dirlist;

typedef short int		t_params;

t_fileinfo				*lsfile(char *dname, t_params opts);
void					new_filelist(char *infos, unsigned int atime, t_fileinfo **onode);
t_params				parse_args(char *av);
void					ls_out(t_fileinfo *flist, int rev);
void					fflist_add(t_list **file_list, char *fname);

#endif
