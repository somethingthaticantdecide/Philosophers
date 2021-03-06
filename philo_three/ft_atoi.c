/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmontagu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/31 21:45:25 by jmontagu          #+#    #+#             */
/*   Updated: 2020/11/01 15:43:25 by jmontagu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

int	ft_atoi(const char *str)
{
	long	result;
	int		index;
	int		sign;

	result = 0;
	sign = 1;
	index = 0;
	if (!str)
		return (0);
	while (str[index] == '\n' || str[index] == '\t' || str[index] == '\v'
		|| str[index] == '\f' || str[index] == '\r' || str[index] == ' ')
		index++;
	if (str[index] == '-' || str[index] == '+')
		if (str[index++] == '-')
			sign = -1;
	while (str[index] >= '0' && str[index] <= '9' && str[index] != '\0')
	{
		result = (result * 10) + str[index++] - 48;
		if (result > 2147483647 && sign == 1)
			return (-1);
		if (result > 2147483648 && sign == -1)
			return (0);
	}
	return (result * sign);
}
