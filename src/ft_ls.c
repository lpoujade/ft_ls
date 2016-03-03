/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   src/ft_ls.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpoujade <lpoujade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/11 14:14:04 by lpoujade          #+#    #+#             */
/*   Updated: 2016/03/03 15:28:23 by lpoujade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int		main(int ac, char **av)
{
	t_params	opts;
	int			ap;
	int			end_args;

	end_args = 0;
	opts = 0;
	ap = 0;
	while (++ap < ac)
	{
		if (*av[ap] == '-' && !end_args)
		{
			if (*(av[ap] + 1) == '-')
			{
				ft_putendl("END ARGS");
				end_args = 1;
			}
			else
				opts |= parse_args(av[ap]);
		}
		else
			ls_out(lsfile(av[ap], opts), opts&0x02);
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
	//
	//
	// FINAL (?)
	// - eval CLI arguments
	// 		- parse args
	// 		- fill a list : simple files first, folders last ( alphanum sorting, or time if -t )
	// - then : 
	// 		- print files infos
	// 		- in folder list : launch lsdir
