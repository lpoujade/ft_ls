/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpoujade <lpoujade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/28 16:18:55 by lpoujade          #+#    #+#             */
/*   Updated: 2015/12/14 18:59:37 by lpoujade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	ft_striter(char *s, void (*f)(char *))
{
	int		index;
	char	*c;

	index = 0;
	while (s[index])
	{
		c = (s + index);
		(f)(c);
		index++;
	}
}
