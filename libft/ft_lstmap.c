/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngragas <ngragas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/20 21:07:53 by ngragas           #+#    #+#             */
/*   Updated: 2020/11/21 21:41:16 by ngragas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*begin;
	t_list	*cur;
	t_list	*last;

	begin = NULL;
	while (lst)
	{
		cur = ft_lstnew(f(lst->content));
		if (cur == NULL)
		{
			ft_lstclear(&begin, del);
			return (NULL);
		}
		if (!begin)
			begin = cur;
		else
			last->next = cur;
		last = cur;
		lst = lst->next;
	}
	return (begin);
}

// Reuse list elements, but change their content.
t_list	*ft_lstconv(t_list *lst, void *(*f)(void *))
{
	t_list	*converted_list;

	converted_list = NULL;
	while (lst)
		ft_lstadd_back(&converted_list, ft_lstpopconv(&lst, f));
	return (converted_list);
}

t_list	*ft_lstconv_xd(t_list *lst,
						void *(*f)(void *, void *), void *extra_data)
{
	t_list	*converted_list;

	converted_list = NULL;
	while (lst)
		ft_lstadd_back(&converted_list, ft_lstpopconv_xd(&lst, f, extra_data));
	return (converted_list);
}
