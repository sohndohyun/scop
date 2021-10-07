/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsohn <dsohn@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/29 22:50:38 by dsohn             #+#    #+#             */
/*   Updated: 2021/03/10 03:02:07 by dsohn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static int	ft_countblock(const char *s1, char c)
{
	int	cnt;
	int	isf;

	cnt = 0;
	isf = 1;
	while (*s1)
	{
		if (*s1 == c)
			isf = 1;
		else
		{
			if (isf)
				cnt++;
			isf = 0;
		}
		s1++;
	}
	return (cnt);
}

static int	ft_blocklen(const char *s1, char c)
{
	const char	*p;

	p = s1;
	while (*s1 && *s1 != c)
		s1++;
	return (s1 - p);
}

static char	*ft_deallocresult(char **result, int i)
{
	while (--i >= 0)
		free(result[i]);
	free(result);
	return (NULL);
}

char	**ft_split(const char *s1, char c)
{
	int		bcnt;
	int		blen;
	char	**result;
	int		i;

	if (s1 == NULL)
		return (NULL);
	bcnt = ft_countblock(s1, c);
	result = (char **)malloc(sizeof(char *) * (bcnt + 1));
	if (!result)
		return (NULL);
	result[bcnt] = 0;
	i = 0;
	while (i < bcnt)
	{
		while (*s1 && *s1 == c)
			s1++;
		blen = ft_blocklen(s1, c);
		result[i] = (char *)malloc(sizeof(char) * (blen + 1));
		if (!result[i])
			return ((char **)ft_deallocresult(result, i));
		ft_strlcpy(result[i++], s1, blen + 1);
		s1 += blen;
	}
	return (result);
}

int	ft_split_cnt(char **line)
{
	int	i;

	if (line == NULL)
		return (0);
	i = 0;
	while (line[i])
		i++;
	return (i);
}
