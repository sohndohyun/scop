/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atod.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsohn <dsohn@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/13 03:07:17 by dsohn             #+#    #+#             */
/*   Updated: 2021/03/10 03:08:37 by dsohn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

double	ft_atod(const char *str)
{
	double	val;
	double	multiple;
	double	sign;

	val = 0;
	multiple = 1;
	sign = 1;
	while (*str == ' ' || *str == '\n' || *str == '\t' || \
			*str == '\v' || *str == '\f' || *str == '\r')
		++str;
	if (*str == '-')
		sign = -1;
	if (*str == '-' || *str == '+')
		++str;
	while (ft_isdigit(*str))
		val = val * 10 + *str++ - '0';
	if (*str == '.')
		str++;
	while (ft_isdigit(*str))
	{
		val = val * 10 + *str++ - '0';
		multiple *= 0.1;
	}
	return (sign * val * multiple);
}
