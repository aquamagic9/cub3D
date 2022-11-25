/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junseo <junseo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 15:32:25 by junseo            #+#    #+#             */
/*   Updated: 2022/06/22 22:51:30 by junseo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*list_new;

	list_new = (t_list *)malloc(sizeof(t_list));
	if (list_new == NULL)
		return (NULL);
	list_new->content = content;
	list_new->next = NULL;
	return (list_new);
}
