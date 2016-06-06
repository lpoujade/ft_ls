/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpoujade <lpoujade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/28 15:54:22 by lpoujade          #+#    #+#             */
/*   Updated: 2015/12/08 18:55:27 by lpoujade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(char const *s1, char const *s2, size_t n)
{
	size_t	i;
	size_t	j;

	if (!*s2 || !s2)
		return ((char *)s1);
	j = 0;
	while (s1[j] && j < n)
	{
		i = 0;
		while (s1[j + i] == s2[i] && (i + j) < n)
		{
			i++;
			if (!s2[i])
				return ((char *)&s1[j]);
		}
		j++;
	}
	return (NULL);
}
