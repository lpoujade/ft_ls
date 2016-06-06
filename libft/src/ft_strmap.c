/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpoujade <lpoujade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/27 15:28:50 by lpoujade          #+#    #+#             */
/*   Updated: 2015/12/04 18:50:46 by lpoujade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmap(char const *s, char (*f)(char))
{
	int		index;
	char	*ret;

	if (!(ret = ft_strnew(ft_strlen(s))))
		return (ret);
	index = 0;
	while (s[index])
	{
		ret[index] = (*f)(s[index]);
		index++;
	}
	ret[index] = '\0';
	return (ret);
}
