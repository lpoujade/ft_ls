/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   src/ft_ls.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpoujade <lpoujade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/11 14:14:04 by lpoujade          #+#    #+#             */
/*   Updated: 2016/03/17 16:43:55 by lpoujade         ###   ########.fr       */
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
			fflist_add(&file_list, av[ap]);		// TODO sorting method
	}
	if (!file_list)
	{
		fflist_add(&file_list, ".");
		fold_list(&file_list, ".", opts);
		file_list = file_list->next;
	}
	//ls_out(eval(&file_list, opts), opts & 0x02);	// TODO output format : like file/file/file \n folder:\n(num)\n files/files/files
	eval(&file_list, opts);
	return (errno ? 1 : 0);
}
