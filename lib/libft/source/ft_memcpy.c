/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsohn <dsohn@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/29 13:08:02 by dsohn             #+#    #+#             */
/*   Updated: 2020/09/30 16:11:36 by dsohn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	const unsigned char		*s = src;
	unsigned char			*d;

	if (dst == NULL && src == NULL)
		return (NULL);
	d = dst;
	while (n--)
		*d++ = *s++;
	return (dst);
}
