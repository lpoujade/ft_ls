/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpoujade <lpoujade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/28 20:53:31 by lpoujade          #+#    #+#             */
/*   Updated: 2015/12/14 18:59:45 by lpoujade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	ft_striteri(char *s, void (*f)(unsigned int, char *))
{
	int		index;
	char	*c;

	index = 0;
	while (s[index])
	{
		c = (s + index);
		(f)(index, c);
		index++;
	}
}
