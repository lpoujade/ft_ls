/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpoujade <lpoujade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/28 14:27:14 by lpoujade          #+#    #+#             */
/*   Updated: 2015/12/02 22:51:14 by lpoujade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_strncmp(char const *s1, char const *s2, size_t n)
{
	if (ft_strlen(s1) >= n && ft_strlen(s2) >= n)
		return (ft_memcmp(s1, s2, n));
	else
	{
		if (ft_strlen(s1) > ft_strlen(s2))
			return (ft_memcmp(s1, s2, ft_strlen(s2) + 1));
		else
			return (ft_memcmp(s1, s2, ft_strlen(s1) + 1));
	}
}
