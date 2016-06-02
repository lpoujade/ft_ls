/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpoujade <lpoujade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/02 14:49:43 by lpoujade          #+#    #+#             */
/*   Updated: 2016/06/02 14:49:50 by lpoujade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

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
