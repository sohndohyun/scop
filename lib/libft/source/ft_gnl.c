/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_gnl.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsohn <dsohn@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/05 01:15:24 by dsohn             #+#    #+#             */
/*   Updated: 2021/03/10 03:52:30 by dsohn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <limits.h>
#include <stdlib.h>
#include <unistd.h>

static int	isline(char *str)
{
	char	*temp;

	if (!str)
		return (-1);
	temp = str;
	while (*str)
	{
		if (*str == '\n')
			return (str - temp);
		str++;
	}
	return (-1);
}

static int	get_line(char **buf, int nline, char **line)
{
	char	*temp;
	int		len;

	*line = (char *)malloc(sizeof(char) * (nline + 1));
	if (!(*line))
		return (-1);
	temp = NULL;
	ft_memcpy(*line, *buf, nline);
	(*line)[nline] = 0;
	len = ft_strlen(*buf + nline + 1);
	if (len > 0)
	{
		temp = (char *)malloc(sizeof(char) * (len + 1));
		if (!temp)
			return (-1);
		ft_memcpy(temp, *buf + nline + 1, len);
		temp[len] = 0;
	}
	free(*buf);
	*buf = temp;
	return (1);
}

static int	return_left(int rlen, char **buf, char **line)
{
	int	len;

	if (rlen < 0)
		return (-1);
	len = isline(*buf);
	if (len >= 0)
		return (get_line(buf, len, line));
	else if (*buf)
	{
		*line = *buf;
		*buf = NULL;
		return (0);
	}
	*line = (char *)malloc(sizeof(char));
	if (!(*line))
		return (-1);
	(*line)[0] = 0;
	return (0);
}

int	ft_gnl(int fd, char **line)
{
	static char		*save[OPEN_MAX] = {NULL, };
	char			buf[BUFFER_SIZE + 1];
	int				rlen;

	if (fd < 0 || OPEN_MAX < fd || !line || BUFFER_SIZE < 1)
		return (-1);
	while (1)
	{
		rlen = read(fd, buf, BUFFER_SIZE);
		if (rlen <= 0)
			break ;
		buf[rlen] = 0;
		save[fd] = ft_freejoin(save[fd], buf);
		rlen = isline(save[fd]);
		if (rlen >= 0)
			return (get_line(&save[fd], rlen, line));
	}
	return (return_left(rlen, &save[fd], line));
}
