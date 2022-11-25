/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junseo <junseo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/13 23:29:14 by junseo            #+#    #+#             */
/*   Updated: 2022/06/22 22:52:31 by junseo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*result;
	size_t	start;
	size_t	end;

	if (!s1 || !set)
		return (NULL);
	start = 0;
	end = ft_strlen(s1);
	while (s1[start] != '\0' && ft_strchr(set, s1[start]))
		start++;
	while (start < end && ft_strchr(set, s1[end]))
		end--;
	if (start >= end)
		return (ft_strdup(""));
	result = (char *)malloc(sizeof(char) * (end - start) + 2);
	if (result == NULL)
		return (NULL);
	ft_strlcpy(result, &s1[start], (end - start) + 2);
	return (result);
}
