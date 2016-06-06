/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpoujade <lpoujade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/28 12:16:09 by lpoujade          #+#    #+#             */
/*   Updated: 2015/12/12 11:48:54 by lpoujade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dest, void const *src, int c, size_t len)
{
	int					index;
	void				*ret;
	unsigned char		cu;
	unsigned char		*tmp_d;
	unsigned const char *tmp_s;

	cu = (unsigned char)c;
	index = 0;
	tmp_d = (unsigned char *)dest;
	tmp_s = (unsigned char const *)src;
	while (len && tmp_s[index] != cu)
	{
		tmp_d[index] = tmp_s[index];
		len--;
		index++;
	}
	if (tmp_s[index] == cu)
	{
		tmp_d[index] = cu;
		ret = (void *)(tmp_d + (index + 1));
	}
	else
		ret = NULL;
	return (ret);
}
