/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   src/ft_ls.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpoujade <lpoujade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/11 14:14:04 by lpoujade          #+#    #+#             */
/*   Updated: 2016/02/12 16:49:03 by lpoujade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int		main(int ac, char **av)
{
	t_fileinfo *f;
	t_params	opts = 6;

	//opts = (av[1][0] == '-') ? parse_args(av, ac) : 0;

	ac--;
	while (ac--)
	{
		av++;
		f=lsdir(*av, opts);
		ls_out(f);
	}
	//
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
	// 		- else file or folder name, get and prints infos with actuals opts.
	return (0);
}
