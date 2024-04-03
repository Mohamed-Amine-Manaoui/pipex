/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmanaoui <mmanaoui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 06:45:48 by mmanaoui          #+#    #+#             */
/*   Updated: 2024/03/31 02:36:16 by mmanaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_lstadd_back_m(t_malloc **lst, t_malloc *new)
{
	t_malloc	*last;

	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	last = *lst;
	while (last->next != NULL)
		last = last->next;
	last->next = new;
}

t_malloc	*ft_lstnew_m(void *data)
{
	t_malloc	*ptr;

	ptr = malloc(sizeof(t_malloc));
	if (ptr == NULL)
		return (NULL);
	ptr->data = data;
	ptr->next = NULL;
	return (ptr);
}

void	*ft_malloc(size_t size, char f_or_m)
{
	void			*ptr;
	static t_malloc	*head;
	t_malloc		*tmp;

	if (f_or_m == 'f')
	{
		while (head)
		{
			tmp = head->next;
			free(head->data);
			free(head);
			head = tmp;
		}
		head = NULL;
		return (NULL);
	}
	ptr = malloc(size);
	ft_lstadd_back_m(&head, ft_lstnew_m(ptr));
	return (ptr);
}
