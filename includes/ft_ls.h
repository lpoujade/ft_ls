/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   includes/ft_ls.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpoujade <lpoujade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/11 14:08:46 by lpoujade          #+#    #+#             */
/*   Updated: 2016/02/12 16:33:03 by lpoujade         ###   ########.fr       */
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
# include "libft.h"

typedef struct			s_fileinfo
{
	char				*infos;
	unsigned int		epoch;
	struct s_fileinfo	*next;
	struct s_fileinfo	*prev;
}						t_fileinfo;

typedef short int		t_params;

typedef struct			s_dirlist
{
	char				*dirname;
	struct s_listdir	*next;
}						t_dirlist;

t_fileinfo				*lsdir(char *dname, t_params opts); // params
t_params				parse_args(char *av);
void					ls_out(t_fileinfo *flist);

#endif
