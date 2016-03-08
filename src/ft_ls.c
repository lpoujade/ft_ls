/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   src/ft_ls.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpoujade <lpoujade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/11 14:14:04 by lpoujade          #+#    #+#             */
/*   Updated: 2016/03/07 14:40:49 by lpoujade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int		main(int ac, char **av)
{
	t_params	opts;
	int			ap;
	int			end_args;
	t_list		*file_list;
	t_list		*prev_file_list;

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
				if (!(opts |= parse_args(av[ap])))
				{
					perror(ft_strjoin("ls: ", av[ap]));
					return (errno);
				}
		}
		else
			fflist_add(&file_list, av[ap]);
	}
	if (file_list)
		while (file_list)
		{
			ls_out(lsfile(file_list->content, opts), opts&0x02);
			prev_file_list = file_list;
			file_list = file_list->next;
			ft_memdel((void**)&prev_file_list);
			if (prev_file_list)
				ft_putendl("FAIL");
		}
	else
		ls_out(lsfile(".", opts), opts&0x02);

	// complete file list using folder list (? -R)
	// eval file list if needed (? -laAt)


	// print file list (? -r)
	//ls_out(flist, opts&0x02);

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
