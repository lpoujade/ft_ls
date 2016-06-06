/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strclchr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpoujade <lpoujade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/26 14:13:22 by lpoujade          #+#    #+#             */
/*   Updated: 2016/03/11 13:20:30 by lpoujade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_strclchr(char const *s, char c)
{
	int		len;
	char	*str;

	if (!s)
		return (0);
	str = (char *)s;
	len = 0;
	while (*str != c && *str)
	{
		str++;
		len++;
	}
	return (len);
}
