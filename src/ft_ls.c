/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   src/ft_ls.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpoujade <lpoujade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/11 14:14:04 by lpoujade          #+#    #+#             */
/*   Updated: 2016/02/11 14:35:26 by lpoujade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int		main(int ac, char **av)
{
	t_dirlist	dirs;
	t_params	pm;

	if (av[1][0] == '-');
		//parse arg struct

	// from **av[1/2] -> av[ac -1] : parse dirlist

	// apply lsdir(char dirname, t_params opts) on each dir in dirlist.
	// 		- if -R option, this function will add folder's name in dirlist
	// 		- this function manage : -R, -l, -a, -t
	// 		- by default use a alphabetical comparison to insert file in the list, if -t passed insert based on times
	// then ( in while loop ) print & del actual file list
	// 		-r will cause to print the list from end to start ( so double-chained list ? )
	
	// free dirlist
	// exit
}
