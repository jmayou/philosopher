/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ulils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmayou <jmayou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 22:16:49 by jmayou            #+#    #+#             */
/*   Updated: 2024/12/12 22:17:24 by jmayou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(const char *str)
{
	int	i;
	int	k;
	int	nb;

	i = 0;
	nb = 0;
	k = 0;
	while (str[i] && ((str[i] >= 9 && str[i] <= 13) || str[i] == ' '))
		i++;
	if (str[i] == '-')
		return (-1);
	else if (str[i] == '+')
		i++;
	k = i;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (-1);
		i++;
	}
	i = k;
	while (str[i] && str[i] >= '0' && str[i] <= '9')
		nb = (nb * 10) + (str[i++] - '0');
	return (nb);
}
