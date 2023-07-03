/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkintana <gkintana@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/04 15:21:45 by gkintana          #+#    #+#             */
/*   Updated: 2022/07/02 13:57:19 by gkintana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*head;

	head = *lst;
	while (*lst)
	{
		*lst = (*lst)->next;
		ft_lstdelone(head, del);
		head = *lst;
	}
	head = NULL;
}
