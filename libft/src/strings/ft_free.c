/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lolaparr <lolaparr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 20:50:19 by lolaparr          #+#    #+#             */
/*   Updated: 2023/10/17 20:50:19 by lolaparr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_free(char **ptr)
{
	free(*ptr);
	*ptr = NULL;
}

void	my_free(char **str, int n)
{
	while (n)
	{
		if (str[n])
		{
			free(str[n]);
			str[n] = NULL;
		}
		n--;
	}
	free(str);
}
