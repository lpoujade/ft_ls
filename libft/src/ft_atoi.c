/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpoujade <lpoujade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/02 11:10:45 by lpoujade          #+#    #+#             */
/*   Updated: 2015/12/13 10:15:18 by lpoujade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		ft_isspace(int c)
{
	int ret;

	ret = 0;
	if (c == '\t' || c == '\n' || c == ' ' || c == '\v' || c == '\f' \
			|| c == '\r')
		ret = 1;
	return (ret);
}

int				ft_atoi(char const *s)
{
	int ret;
	int i;
	int neg;

	i = 0;
	ret = 0;
	neg = 1;
	while (ft_isspace(s[i]))
		i++;
	if (s[i] == '-' && ft_isdigit(s[i + 1]))
	{
		i++;
		neg = -1;
	}
	else if ((s[i] == '+') && ft_isdigit(s[i + 1]))
		i++;
	while (ft_isdigit(s[i]))
	{
		ret = ret * 10;
		ret = ret + (s[i] - '0');
		i++;
	}
	return (ret * neg);
}
