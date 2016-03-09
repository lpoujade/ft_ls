/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   src/ft_ls.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpoujade <lpoujade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/11 14:14:04 by lpoujade          #+#    #+#             */
/*   Updated: 2016/03/09 12:57:03 by lpoujade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int		main(int ac, char **av)
{
	t_params	opts;
	int			ap;
	int			end_args;
	t_fileinfo	*file_list;

	file_list = NULL;
	end_args = 0;
	opts = 0;
	ap = 0;
	// args list parsing ( opts & files )
	while (++ap < ac)
	{
		if (*av[ap] == '-' && !end_args)
		{
			if (*(av[ap] + 1) == '-')
				end_args = 1;
			else
				opts |= parse_args(av[ap]);
		}
		else
			fflist_add(&file_list, av[ap]);
	}
	if (file_list)
		while (file_list)
		{
			ls_out(lsfile(file_list->infos, opts), opts&0x02);
			file_list = file_list->next;
		}
	else
		ls_out(lsfile(".", opts), opts&0x02);

	// complete file list using folder list (? -R)
	// eval file list if needed (? -laAt)


	// print file list (? -r)
	//ls_out(flist, opts&0x02);

	return (errno ? 1 : 0);
}

	// list arguments and for each :
	// 		- if actual char begin with '-', add to t_params opts, till -- was encoutered ( ? --word options ? POSIX ? )
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
