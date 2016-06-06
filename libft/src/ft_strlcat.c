/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpoujade <lpoujade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/28 19:39:25 by lpoujade          #+#    #+#             */
/*   Updated: 2015/12/08 09:43:45 by lpoujade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t		ft_strlcat(char *dest, char const *src, size_t size)
{
	char	*tmp_d;
	int		i;
	size_t	max;
	size_t	o_size;

	o_size = size;
	max = ft_strlen(dest);
	tmp_d = dest;
	while (*tmp_d && size)
	{
		tmp_d++;
		size--;
	}
	if (!size)
		return (o_size + ft_strlen(src));
	i = 0;
	while (src[i] && --size)
	{
		*tmp_d = src[i];
		tmp_d++;
		i++;
	}
	if (size && !src[i])
		*tmp_d = '\0';
	return (max + ft_strlen(src));
}
