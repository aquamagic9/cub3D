/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junseo <junseo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 13:32:35 by junseo            #+#    #+#             */
/*   Updated: 2022/06/22 22:52:07 by junseo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char*))
{
	unsigned int	i;
	unsigned int	str_len;

	if (!s || !f)
		return ;
	str_len = (unsigned int)ft_strlen(s);
	i = 0;
	while (i < str_len)
	{
		f(i, s + i);
		i++;
	}
}
