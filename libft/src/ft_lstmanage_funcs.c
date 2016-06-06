/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmanages_funcs.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpoujade <lpoujade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/03 14:24:42 by lpoujade          #+#    #+#             */
/*   Updated: 2016/04/28 12:46:40 by lpoujade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstiter(t_list *lst, void (*f)(t_list *elem))
{
	t_list *tmp;

	tmp = lst;
	if (f)
	{
		while (tmp)
		{
			(f)(tmp);
			tmp = tmp->next;
		}
	}
}

void	ft_lstdel(t_list **alst, void (*del)(void *))
{
	t_list *tmp;
	t_list *nxt;

	tmp = *alst;
	while (tmp)
	{
		nxt = tmp->next;
		(del)(tmp);
		ft_memdel((void**)&tmp);
		tmp = nxt;
	}
	*alst = NULL;
}

void	ft_lstdelone(t_list **alst, void (*del)(void *))
{
	(del)((*alst));
	free(*alst);
	*alst = NULL;
}
