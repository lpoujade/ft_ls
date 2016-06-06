/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpoujade <lpoujade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/26 13:34:06 by lpoujade          #+#    #+#             */
/*   Updated: 2016/01/22 13:23:00 by lpoujade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncat(char *s1, const char *s2, size_t n)
{
	int	s_s1;

	s_s1 = ft_strlen(s1);
	ft_strncpy((s1 + ft_strlen(s1)), s2, n);
	s1[s_s1 + n] = 0;
	return (s1);
}
