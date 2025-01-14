/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lolaparr <lolaparr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 21:18:17 by lolaparr          #+#    #+#             */
/*   Updated: 2023/10/16 21:18:17 by lolaparr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

long long	ft_atoi(const char *str)
{
	int					i;
	unsigned long long	nbr;
	int					signe;

	signe = 1;
	nbr = 0;
	i = 0;
	while ((str[i] >= '\t' && str[i] <= '\r') || str[i] == ' ')
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			signe *= -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		nbr = nbr * 10 + (str[i] - '0');
		i++;
	}
	if (nbr > (unsigned long)LONG_MAX && signe > 0)
		nbr = LONG_MAX;
	else if (nbr > (unsigned long)LONG_MAX + 1 && signe < 0)
		nbr = (unsigned long)LONG_MAX + 1;
	return (nbr * signe);
}
