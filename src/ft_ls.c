/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   src/ft_ls.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpoujade <lpoujade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/11 14:14:04 by lpoujade          #+#    #+#             */
/*   Updated: 2016/02/15 23:01:47 by lpoujade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int		main(int ac, char **av)
{
	t_params	opts;
	int			ap;

	opts = 0;
	ap = 1;
	while (ap <= ac - 1 && *av[ap] == '-')
	{
		if (*(av[ap] + 1) == '-' && ap++)
			break ;
		opts |= parse_args(av[ap]);
		ap++;
	}
	if (ap >= ac)
	{
		ls_out(lsfile(".", opts), opts&0x02);
		return (0);
	}
	while (ap <= ac - 1)
	{
		ls_out(lsfile(av[ap], opts), opts&0x02);
		if (ap != ac - 1)
			ft_putendl(ft_strjoin("\n\n", ft_strjoin(av[ap + 1], ":")));
		ap++;
	}
	return (0);
}

	// from **av[1/2] -> av[ac -1] : parse dirlist

	// apply lsdir(char dirname, t_params opts) on each dir in dirlist.
	// 		- this function return a s_fileinfo within folder in s_dirlist
	// 				-R will add listed folder's name after actual dir in dirlist
	// 				-t will change sorting condition : access time in place of alphabetical order
	// 				-l will save more info in fileinfo->infos (-R: permissions, ?, user, group, size, date) filename
	// 				-a will cause to not exclude '.'-begining files
	//
	// then ( in same loop ) print & del actual file list
	// 		- if not first dirname (?)
	// 		-r will cause to print the list from end to start ( so double-chained list ? )

	// free dirlist
	// exit
	//
	//
	// --- or --
	//
	// list arguments and for each :
	// 		- if actual char begin with '-', add to t_params opts,
	// 		- else file or folder name, get and prints infos with actuals opts. ( here if file = folder AND -R option -> add each sub-folders to *dirlist)
