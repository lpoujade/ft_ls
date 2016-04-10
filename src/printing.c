/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   src/printing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpoujade <lpoujade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/20 18:46:23 by lpoujade          #+#    #+#             */
/*   Updated: 2016/04/10 11:37:52 by lpoujade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

inline void	st_fputstr(char **details, int *nbrmax)
{
	int c;
	int	step;

	c = 0;
	while (*details && c <= 7)
	{
		if (**details)
		{
			step = nbrmax[c] - ft_strlen(*details);
			step < 0 ? step = 10 : 0;
			c == 3 || c == 2 ? ft_putstr(*details) : 0;
			if (nbrmax[c] < 20)
				while (step-- > 0)
					write(1, " ", 1);
			c != 3 && c != 2 ? ft_putstr(*details) : 0;
			ft_putstr("  ");
		}
		c++;
		details++;
	}
}

inline void	pdir_infos(t_fileinfo *dir, int first_time, t_params opts)
{
	if (first_time)
	{
		ft_putstr(opts & LONG_FORMAT ? "\n" : "\n\n");
		ft_putstr(dir->infos);
		ft_putstr(":\n");
	}
	if (opts & LONG_FORMAT && dir->fcount > 0)
	{
		ft_putstr("total ");
		ft_putnbr(dir->fcount);
		ft_putchar('\n');
	}
}
