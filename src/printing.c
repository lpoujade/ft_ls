/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   src/printing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpoujade <lpoujade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/20 18:46:23 by lpoujade          #+#    #+#             */
/*   Updated: 2016/05/18 13:55:23 by lpoujade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void		st_fputstr(char **details, int *nbrmax)
{
	int c;
	int	step;

	c = 0;
	while (*details && c <= 7)
	{
		if (*details && **details)
		{
			if (nbrmax)
				step = nbrmax[c] - ft_strlen(*details);
			else
				step = 10;
			c == 3 || c == 2 ? ft_putstr(*details) : 0;
			if (step < 20 && c != 6 && c > 0)
				while (step-- > 0)
					write(1, " ", 1);
			c != 3 && c != 2 ? ft_putstr(*details) : 0;
			ft_putstr(" ");
		}
		c++;
		details++;
	}
}

inline void	pdir_infos(t_fileinfo *dir, short *first_time, t_params opts)
{
	if (!*first_time || !ft_strcmp(dir->infos, "./"))
	{
		ft_putstr(opts & LONG_FORMAT ? "\n" : "\n\n");
		ft_putstr(dir->infos);
		ft_putstr(":\n");
	}
	else
		*first_time = 0;
	if (opts & LONG_FORMAT && dir->fcount > 0)
	{
		ft_putstr("total ");
		ft_putnbr(dir->fcount);
		ft_putchar('\n');
	}
}
