/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   src/subfuncs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpoujade <lpoujade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/26 15:55:39 by lpoujade          #+#    #+#             */
/*   Updated: 2016/05/16 11:20:06 by lpoujade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int			fts_strcmp(t_list *s1, t_list *s2)
{
	int				i;
	unsigned char	*a;
	unsigned char	*b;

	a = (unsigned char*)((t_fileinfo*)s1)->infos;
	b = (unsigned char*)((t_fileinfo*)s2)->infos;
	i = 0;
	while (a[i] && b[i] && a[i] == b[i])
		i++;
	return (a[i] - b[i]);
}

void		ls_out(t_fileinfo *flist, t_params opts)
{
	while (flist)
	{
		ft_putstr(flist->infos);
		if (!(opts & LONG_FORMAT))
			ft_putchar('\t');
		flist = (t_fileinfo*)flist->next;
	}
}

int			ftime_cmp(t_list *f1, t_list *f2)
{
	struct stat		file;
	time_t			fst;

	while (f1->next && *((t_fileinfo*)f1)->infos)
		f1 = f1->next;
	if ((lstat(((t_fileinfo*)f1)->infos, &file) == -1))
		perror(ft_strjoin("ls: lstat: ", ((t_fileinfo*)f1)->infos));
	fst = file.st_atime;
	ft_bzero(&file, sizeof(struct stat));
	if ((lstat(((t_fileinfo*)f2)->infos, &file) == -1))
		perror("ls: lstat: ");
	if ((double)fst < (double)file.st_atime)
		return (1);
	else if ((double)fst > (double)file.st_atime)
		return (-1);
	else
		return (fts_strcmp(f1, f2));
	return (0);
}

char		*fts_date(time_t const *clock)
{
	char	*date;
	char	*t_buf;
	time_t	act;

	date = ft_strnew(13);
	t_buf = ctime(clock);
	date = ft_strncpy(date, t_buf + 4, 12);
	if ((time(&act) - *clock) >= 13042800 || act < *clock)
		ft_strncpy(date + 7, t_buf + 19, 5);
	return (date);
}

inline char	*epure_name(char *fname, t_params opts)
{
	char *slash;

	if (!(opts & FULL_NAMES) && (slash = ft_strrchr(fname, '/')))
		slash = (*(slash + 1)) ? slash + 1 : fname;
	else
		slash = fname;
	return (slash);
}
