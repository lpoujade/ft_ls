/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpoujade <lpoujade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/27 22:36:49 by lpoujade          #+#    #+#             */
/*   Updated: 2015/12/14 19:02:55 by lpoujade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, void const *src, size_t n)
{
	char		*tmp_d;
	char const	*tmp_s;
	int			index;

	index = 0;
	tmp_d = (char *)dst;
	tmp_s = (char const *)src;
	while (n)
	{
		tmp_d[index] = tmp_s[index];
		n--;
		index++;
	}
	return (dst);
}
