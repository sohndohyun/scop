/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsohn <dsohn@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/29 21:39:13 by dsohn             #+#    #+#             */
/*   Updated: 2021/03/10 03:46:02 by dsohn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strjoin(const char *s1, const char *s2)
{
	size_t	len1;
	size_t	len2;
	char	*dup;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	dup = (char *)malloc(len1 + len2 + 1);
	if (dup)
	{
		ft_memcpy(dup, s1, len1);
		ft_memcpy(dup + len1, s2, len2);
		dup[len1 + len2] = 0;
	}
	return (dup);
}

char	*ft_freejoin(char *s1, const char *s2)
{
	size_t	len1;
	size_t	len2;
	char	*dup;

	if (!s2)
		return (s1);
	if (!s1)
		return (ft_strdup(s2));
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	dup = (char *)malloc(sizeof(char) * (len1 + len2 + 1));
	if (dup)
	{
		ft_memcpy(dup, s1, len1);
		free(s1);
		ft_memcpy(dup + len1, s2, len2);
		dup[len1 + len2] = 0;
	}
	return (dup);
}
