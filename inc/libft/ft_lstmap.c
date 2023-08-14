/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alajara- <alajara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 10:59:53 by alajara-          #+#    #+#             */
/*   Updated: 2022/10/24 09:48:38 by alajara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
Parameters  lst: The address of a pointer to a node.
			f: The address of the function used to iterate on
			the list.
			del: The address of the function used to delete
			the content of a node if needed.

Return value The*new_n list.
			 NULL if the allocation fails.

External functs. malloc, free

Description Iterates the list ’lst’ and applies the function
			’f’ on the content of each node. Creates a*new_n
			list resulting of the successive applications of
			the function ’f’. The ’del’ function is used to
			delete the content of a node if needed.
*/

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_n;
	t_list	*origin;
	void	*new_c;

	origin = NULL;
	while (lst)
	{
		new_c = f(lst -> content);
		new_n = ft_lstnew(new_c);
		if (!new_n)
		{
			free (new_c);
			ft_lstclear (&origin, del);
			return (NULL);
		}
		ft_lstadd_back(&origin, new_n);
		lst = lst -> next;
	}
	return (origin);
}
