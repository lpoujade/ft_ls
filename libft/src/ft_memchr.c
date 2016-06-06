/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpoujade <lpoujade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/28 13:24:18 by lpoujade          #+#    #+#             */
/*   Updated: 2016/02/15 22:31:20 by lpoujade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(void const *s, int c, size_t len)
{
	unsigned int	index;
	void			*ret;
	unsigned char	cu;
	unsigned char	*si;

	cu = (unsigned char)c;
	si = (unsigned char *)s;
	index = 0;
	while (index < len && si[index] != cu)
		index++;
	if (index == len)
		ret = NULL;
	else
		ret = (void *)(si + index);
	return (ret);
}
