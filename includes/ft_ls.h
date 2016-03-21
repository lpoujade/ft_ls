/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   includes/ft_ls.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpoujade <lpoujade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/11 14:08:46 by lpoujade          #+#    #+#             */
/*   Updated: 2016/03/21 23:32:15 by lpoujade         ###   ########.fr       */
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
	struct s_fileinfo	*next;
	struct s_fileinfo	*prev;
}						t_fileinfo;

typedef short int		t_params;

void			fflist_add(t_fileinfo **file_list, char *fname);
t_fileinfo		*fold_list(char *dname, t_params opts);
t_fileinfo		*eval(t_fileinfo **fflist, t_params opts, int c);
void			print_file_infos(struct stat details, char *fname, t_params opts);
t_params		parse_args(char *av);
void			ls_out(t_fileinfo *flist, t_params opts);
void			node_insert_strcmp(t_fileinfo **fflist, t_fileinfo *node);
void			node_add(t_fileinfo **fflist, t_fileinfo *new);

#endif
