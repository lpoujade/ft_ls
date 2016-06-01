/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lists.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpoujade <lpoujade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/01 12:47:58 by lpoujade          #+#    #+#             */
/*   Updated: 2016/06/01 17:09:09 by lpoujade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_list		*fts_new(char const *fname, t_params opts)
{
	t_files	*new;

	if (!(new = (t_files*)malloc(sizeof(t_files))))
	{
		perror(ft_strjoin("ls: ", fname));
		exit(3);
	}
	new->next = NULL;
	new->prev = NULL;
	new->path = NULL;
	new->name = NULL;
	new->details = NULL;
	new->fcount = 0;
	new->subfiles = NULL;
	pfile_infos(new, ft_strdup(fname), opts);
	return ((t_list *)new);
}

void		fts_delnode(t_files *node)
{
	if (node)
	{
		if (node->details)
			free(node->details);
		free(node);
	}
	node = NULL;
}

int			fts_strcmp(t_list *s1, t_list *s2)
{
	int				i;
	unsigned char	*a;
	unsigned char	*b;

	a = (unsigned char*)((t_files*)s1)->name;
	b = (unsigned char*)((t_files*)s2)->name;
	i = 0;
	while (a[i] && b[i] && a[i] == b[i])
		i++;
	return (a[i] - b[i]);
}

int			fts_timecmp(t_list *of1, t_list *of2)
{
	t_files f1;
	t_files f2;

	f1 = *(t_files*)of1;
	f2 = *(t_files*)of2;
	if ((double)f1.stmp.tv_sec < (double)f2.stmp.tv_sec)
		return (1);
	else if ((double)f1.stmp.tv_sec > (double)f2.stmp.tv_sec)
		return (-1);
	else if ((double)f1.stmp.tv_nsec < (double)f2.stmp.tv_nsec)
		return (1);
	else if ((double)f1.stmp.tv_nsec > (double)f2.stmp.tv_nsec)
		return (-1);
	else
		return (fts_strcmp(of1, of2));
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

char		*epure_name(char *fname, t_params opts)
{
	char *slash;

	if (!(opts & FULL_NAMES) && (slash = ft_strrchr(fname, '/')))
		slash = (*(slash + 1)) ? slash + 1 : fname;
	else
		slash = fname;
	return (slash);
}
