/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpoujade <lpoujade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/27 23:11:59 by lpoujade          #+#    #+#             */
/*   Updated: 2015/12/18 14:46:15 by lpoujade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, void const *src, size_t len)
{
	unsigned char	*t_src;
	unsigned char	*t_dst;
	size_t			i;

	i = 0;
	t_src = (unsigned char *)src;
	t_dst = (unsigned char *)dst;
	if (t_src < t_dst)
		while (len--)
			t_dst[len] = t_src[len];
	else
		while (i < len)
		{
			t_dst[i] = t_src[i];
			i++;
		}
	return (dst);
}
