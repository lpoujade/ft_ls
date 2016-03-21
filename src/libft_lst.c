/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   src/lists.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpoujade <lpoujade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/12 17:50:35 by lpoujade          #+#    #+#             */
/*   Updated: 2016/03/21 16:18:56 by lpoujade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	fts_lstadd(t_list **alst, t_list *new)
{
	new->next = *alst;
	if ((*alst)->prev)
		(*alst)->prev->next = new;
	(*alst)->prev = new;
	*alst = new;
}

void	fts_lstinsert(t_list **fflist, t_list *new, int (*f)(void*,void*))
{
	t_list		*tmp;
	int			comp;

	tmp = (*fflist);
	while ((comp = (f)((new + 2 * sizeof(t_list*)), (tmp + 2*sizeof(t_list*))) > 0 && tmp->next))
		tmp = tmp->next;
	if (comp > 0)
	{
		if (tmp->next)
			tmp->next->prev = (t_list*)new;
		new->next = (t_list*)tmp->next;
		tmp->next = (t_list*)new;
		new->prev = (t_list*)tmp;
	}
	else
	{
		new->next = tmp;
		new->prev = tmp->prev;
		if (tmp->prev)
			tmp->prev->next = new;
		else
			*fflist = new;
		tmp->prev = new;
	}
}

void	fts_lstappend(t_list *alst, t_list *new)
{
	t_list	*tmp;

	tmp = alst;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
	new->prev = tmp;
}

void	fts_lstiter(t_list *lst, void (*f)(t_list *elem))
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

//t_list		*fts_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
//{
//	t_list	*new;
//	t_list	*tmp;
//	t_list	*d_new;
//
//	d_new = NULL;
//	if (lst && f)
//	{
//		new = fts_lstnew(NULL, 0);
//		d_new = new;
//		tmp = lst;
//		while (tmp)
//		{
//			ft_memcpy(new, (*f)(tmp), sizeof(t_list));
//			if (tmp->next)
//				new->next = fts_lstnew(NULL, 0);
//			new = new->next;
//			tmp = tmp->next;
//		}
//	}
//	return (d_new);
//}

//t_list		*fts_lstnew(void const *content, size_t content_size)
//{
//	t_list	*new;
//
//	if (!(new = (t_list *)malloc(sizeof(t_list))))
//		return (NULL);
//	if (!content)
//	{
//		new->content = NULL;
//		new->content_size = 0;
//	}
//	else
//	{
//		if (!(new->content = malloc(content_size)))
//		{
//			free(new);
//			return (NULL);
//		}
//		ft_memcpy(new->content, content, content_size);
//		new->content_size = content_size;
//	}
//	new->next = NULL;
//	return (new);
//}

//void	fts_lstdel(t_list **alst, void (*del)(void *))
//{
//	t_list *tmp;
//	t_list *nxt;
//
//	tmp = *alst;
//	while (tmp)
//	{
//		nxt = tmp->next;
//		fts_lstdelone(&tmp, (del));
//		tmp = nxt;
//	}
//	*alst = NULL;
//}
//
//void	fts_lstdelone(t_list **alst, void (*del)(void *))
//{
//	(del)((*alst));
//	free(*alst);
//	*alst = NULL;
//}
