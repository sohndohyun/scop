/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsohn <dsohn@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/29 21:59:58 by dsohn             #+#    #+#             */
/*   Updated: 2021/03/10 03:08:58 by dsohn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static size_t	ft_trimstart(const char *s1, const char *set, size_t len)
{
	size_t	i;

	i = -1;
	while (++i < len)
		if (ft_strchr(set, s1[i]) == 0)
			break ;
	return (i);
}

static size_t	ft_trimend(const char *s1, const char *set, size_t len)
{
	size_t	i;

	i = -1;
	while (++i < len)
		if (ft_strchr(set, s1[len - i - 1]) == 0)
			break ;
	return (len - i);
}

char	*ft_strtrim(const char *s1, const char *set)
{
	size_t	len;
	size_t	start;
	size_t	end;
	char	*dup;

	if (s1 == NULL || set == NULL)
		return (NULL);
	len = ft_strlen(s1);
	start = ft_trimstart(s1, set, len);
	end = ft_trimend(s1, set, len);
	if (start < end)
		len = end - start + 1;
	else
		len = 1;
	dup = (char *)malloc(len);
	if (dup)
		ft_strlcpy(dup, s1 + start, len);
	return (dup);
}
