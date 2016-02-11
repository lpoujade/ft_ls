/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   includes/ft_ls.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpoujade <lpoujade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/11 14:08:46 by lpoujade          #+#    #+#             */
/*   Updated: 2016/02/11 14:22:02 by lpoujade         ###   ########.fr       */
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
	struct s_fileinfo	*next;
}						t_fileinfo;

typedef struct		s_params
{
	unsigned int	r : 1;
	unsigned int	l : 1;
	unsigned int	t : 1;
	unsigned int	a : 1;
}					t_params;

typedef struct			s_dirlist
{
	char				*dirname;
	struct s_listdir	*next;
}						t_dirlist;

#endif
