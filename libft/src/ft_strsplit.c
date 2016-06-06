/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpoujade <lpoujade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/10 12:20:44 by lpoujade          #+#    #+#             */
/*   Updated: 2015/12/14 19:01:13 by lpoujade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		how_strings(char const *s, char c)
{
	int	i;
	int	co;

	i = 0;
	co = 0;
	while (s[i])
	{
		while (s[i++] == c)
			if (!s[i])
				return (co);
		while (s[i] != c && s[i])
			i++;
		co++;
	}
	return (co);
}

char			**ft_strsplit(char const *s, char c)
{
	char	**ret;
	int		i;
	int		len;
	int		i_ptr;

	ret = (char **)ft_memalloc((sizeof(char *) * how_strings(s, c)) + 1);
	if (!s || !ret)
		return (NULL);
	i = 0;
	i_ptr = 0;
	while (s[i])
	{
		len = 0;
		while (s[i] == c && s[i])
			i++;
		while (s[i + len] != c && s[i + len])
			len++;
		if (len)
			if (!(ret[i_ptr++] = ft_strsub(s, i, len)))
				return (NULL);
		i = i + len;
	}
	ret[i_ptr] = NULL;
	return (ret);
}
