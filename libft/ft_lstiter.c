/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngragas <ngragas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/20 21:06:03 by ngragas           #+#    #+#             */
/*   Updated: 2020/11/20 21:07:44 by ngragas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	while (lst)
	{
		f(lst->content);
		lst = lst->next;
	}
}

void	ft_lstiterix(t_list *lst, void (*f)(void *data, int ix, int is_last))
{
	int	ix;

	ix = 0;
	while (lst)
	{
		f(lst->content, ++ix, lst->next == NULL);
		lst = lst->next;
	}
}

// Stream process list elements.
// Each element is reused. Its content can change. Processing of an element can
// yield more than one element, but the first one of them would be the element
// itself.
void	ft_lstpipeline(t_list **lst, t_list *(*pipeline)(t_list **))
{
	t_list	*converted_list;

	converted_list = NULL;
	while (*lst)
		ft_lstadd_back(&converted_list, pipeline(lst));
	ft_lstadd_front(lst, converted_list);
}
