/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strinv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpoujade <lpoujade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/29 15:21:48 by lpoujade          #+#    #+#             */
/*   Updated: 2015/12/02 11:44:40 by lpoujade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strinv(char *s)
{
	char	*tmp;
	int		i;
	int		c;

	i = ft_strlen(s) - 1;
	c = 0;
	tmp = ft_strdup(s);
	while (i + 1)
	{
		s[c] = tmp[i];
		i--;
		c++;
	}
	ft_strdel(&tmp);
	return (s);
}
