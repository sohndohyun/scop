/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsohn <dsohn@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/29 21:23:43 by dsohn             #+#    #+#             */
/*   Updated: 2021/03/10 03:03:58 by dsohn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_substr(const char *s, unsigned int start, size_t len)
{
	size_t	slen;
	void	*dup;

	if (s == NULL)
		return (NULL);
	if (ft_strlen(s) < start)
		return (ft_strdup(""));
	slen = ft_strlen(s + start);
	if (len >= slen)
		len = slen;
	dup = malloc(len + 1);
	if (dup)
		ft_strlcpy(dup, s + start, len + 1);
	return (dup);
}
