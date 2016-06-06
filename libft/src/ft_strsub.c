/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpoujade <lpoujade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/26 13:31:50 by lpoujade          #+#    #+#             */
/*   Updated: 2015/12/04 18:28:34 by lpoujade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	char *ret;

	ret = ft_strnew(len);
	if (ret)
	{
		ft_strncat(ret, (s + start), len);
		ft_strcat((ret + ft_strlen(ret)), "\0");
	}
	return (ret);
}
