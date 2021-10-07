/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsohn <dsohn@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/29 13:38:11 by dsohn             #+#    #+#             */
/*   Updated: 2020/09/30 16:11:57 by dsohn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	const unsigned char		*s = src;
	unsigned char			*d;

	if (dst == NULL && src == NULL)
		return (NULL);
	d = dst;
	if (d < s)
		while (len--)
			*d++ = *s++;
	else
	{
		s += (len - 1);
		d += (len - 1);
		while (len--)
			*d-- = *s--;
	}
	return (dst);
}
