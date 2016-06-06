/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpoujade <lpoujade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/26 10:14:23 by lpoujade          #+#    #+#             */
/*   Updated: 2015/12/02 11:46:58 by lpoujade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned long	index;
	char			*b2;
	unsigned char	c2;

	if (len)
	{
		c2 = (unsigned char)c;
		b2 = (char *)b;
		index = 0;
		while (index < len)
		{
			b2[index] = c2;
			index++;
		}
	}
	return (b);
}
