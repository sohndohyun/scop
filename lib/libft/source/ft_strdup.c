/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsohn <dsohn@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/29 21:15:03 by dsohn             #+#    #+#             */
/*   Updated: 2020/09/29 21:20:00 by dsohn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strdup(const char *s1)
{
	size_t	len;
	void	*dup;

	len = ft_strlen(s1) + 1;
	dup = malloc(len);
	if (dup)
	{
		ft_memcpy(dup, s1, len);
	}
	return (dup);
}
