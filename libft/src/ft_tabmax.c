/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tabmax.cbmax.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpoujade <lpoujade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/06 19:38:17 by lpoujade          #+#    #+#             */
/*   Updated: 2016/01/07 13:15:13 by liumsade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_tabmax(int *t, int siz)
{
	int	max;

	max = 0;
	while (siz--)
		if (max < t[siz])
			max = t[siz];
	return (max);
}
