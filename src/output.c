/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpoujade <lpoujade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/01 14:01:11 by lpoujade          #+#    #+#             */
/*   Updated: 2016/06/07 11:53:10 by lpoujade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void				rev_print_slist(t_files *node)
{
	t_files *tmp;

	tmp = node;
	while (tmp)
	{
		if (!tmp->subfiles)
			st_fputstr(tmp->details, tmp->fields_len);
		tmp = (t_files*)tmp->prev;
	}
}

static inline void	print_dirname(t_files *dir, t_params opts)
{
	if (dir->prev || dir->next)
	{
		if (dir->prev || (!dir->prev && dir->subfiles))
			ft_putchar('\n');
		ft_putstr(dir->name);
		ft_putstr(":\n");
	}
	if (opts & LONG_FORMAT && dir->subfiles)
	{
		ft_putstr("total ");
		ft_putnbr(dir->fcount > 0 ? ++dir->fcount : 0);
		ft_putchar('\n');
	}
}

void				rev_recurse_out(t_files *root, t_params opts)
{
	t_files	*tmp;

	tmp = lastnode(root->subfiles);
	if (root->subfiles)
		print_dirname(root, opts);
	while (tmp)
	{
		st_fputstr(tmp->details, root->fields_len);
		tmp = (t_files*)tmp->prev;
	}
	if (!(opts & RECURSIVE))
		return ;
	tmp = lastnode(root->subfiles);
	while (tmp)
	{
		if (tmp->fcount && !ft_strstr(tmp->name, "/..\0"))
			rev_recurse_out(tmp, opts);
		tmp = (t_files*)tmp->prev;
	}
}

void				recurse_out(t_files *root, t_params opts)
{
	t_files		*sons;

	sons = root->subfiles;
	print_dirname(root, opts);
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
		if (sons->fcount && !ft_strstr(sons->name, "/..\0"))
			recurse_out(sons, opts);
		sons = (t_files*)sons->next;
	}
}

void				st_fputstr(char **details, int *nbrmax)
{
	int c;
	int	step;

	c = 0;
	if (!details)
		return ;
	while (details && *details && c <= 7)
	{
		if (*details)
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
