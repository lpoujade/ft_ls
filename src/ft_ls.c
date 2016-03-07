/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   src/ft_ls.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpoujade <lpoujade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/11 14:14:04 by lpoujade          #+#    #+#             */
/*   Updated: 2016/03/07 11:22:12 by lpoujade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int		main(int ac, char **av)
{
	t_params	opts;
	int			ap;
	int			end_args;
	t_list		*file_list;

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
	while (file_list)
	{
		ls_out(lsfile(file_list->content, opts), opts&0x02);
		file_list = file_list->next;
	}

	// complete file list using folder list (? -R)
	// eval file list if needed (? -laAt)

	//ls_out(flist, opts&0x02);

	// print file list (? -r)

	return (0);
}

	// list arguments and for each :
	// 		- if actual char begin with '-', add to t_params opts, till -- was encoutered
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
