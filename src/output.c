/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpoujade <lpoujade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/01 14:01:11 by lpoujade          #+#    #+#             */
/*   Updated: 2016/06/02 16:12:21 by lpoujade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void		recurse_out(t_files *root, t_params opts)
{
	t_files	*sons;

	ft_putchar('\n');
	ft_putstr(root->name);
	sons = root->subfiles;
	ft_putstr(":\n");
	while (sons)
	{
		st_fputstr(sons->details, root->fields_len);
		sons = (t_files*)sons->next;
	}
	sons = root->subfiles;
	if (!(opts & RECURSIVE))
		return ;
	while (sons)
	{
		if (sons->fcount && !ft_strstr(sons->name, "/..\0") &&
				!ft_strstr(sons->name, "/.\0"))
			recurse_out(sons, opts);
		sons = (t_files*)sons->next;
	}
}

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
	ft_putchar('\n');
}
