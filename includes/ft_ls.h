/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   includes/ft_ls.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpoujade <lpoujade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/11 14:08:46 by lpoujade          #+#    #+#             */
/*   Updated: 2016/03/15 12:34:22 by lpoujade         ###   ########.fr       */
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
	char				*infos;
	unsigned int		epoch;
	struct s_fileinfo	*next;
	struct s_fileinfo	*prev;
}						t_fileinfo;

typedef short int		t_params;

void					fold_list(t_fileinfo **fflist, char *dname, t_params opts);
t_fileinfo				*eval(t_fileinfo **fflist, t_params opts);
void					parse_file_infos(char **fname, struct stat *details);
t_params				parse_args(char *av);
void					ls_out(t_fileinfo *flist, int rev);
void					fflist_add(t_fileinfo **file_list, char *fname);
void					fflist_add_end(t_fileinfo **file_list, char *fname);

#endif
