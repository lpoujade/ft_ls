/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   includes/ft_ls.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpoujade <lpoujade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/11 14:08:46 by lpoujade          #+#    #+#             */
/*   Updated: 2016/03/21 15:52:07 by lpoujade         ###   ########.fr       */
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

typedef struct			s_list
{
	struct s_list		*next;
	struct s_list		*prev;
}						t_list;

typedef struct			s_fileinfo
{
	t_list				*next;
	t_list				*prev;
	char				*infos;
}						t_fileinfo;

typedef short int		t_params;

t_params				parse_args(char *av);
t_fileinfo				*fold_list(char *dname, t_params opts);
t_fileinfo				*eval(t_fileinfo **fflist, t_params opts, int c);
void					print_file_infos(struct stat details, char *fname, t_params opts);

void		fflist_add(t_fileinfo **file_list, char *fname);
void		ls_out(t_fileinfo *flist, t_params opts);

// lists
void	fts_lstinsert(t_list **fflist, t_list *new, int (*f)(void*,void*));
void	fts_lstadd(t_list **alst, t_list *new);
void	fts_lstappend(t_list *alst, t_list *new);
void	fts_lstiter(t_list *lst, void (*f)(t_list *elem));;

#endif
