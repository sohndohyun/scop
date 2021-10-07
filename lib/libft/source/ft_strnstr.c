/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsohn <dsohn@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/30 02:09:50 by dsohn             #+#    #+#             */
/*   Updated: 2021/03/10 02:41:25 by dsohn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	nlen;

	if (!*needle)
		return ((char*)haystack);
	nlen = ft_strlen(needle);
	while (*haystack && len-- >= nlen)
	{
		if (*haystack == *needle && ft_memcmp(haystack, needle, nlen) == 0)
			return ((char*)haystack);
		haystack++;
	}
	return (0);
}
