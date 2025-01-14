/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_double_tab.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lolaparr <lolaparr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 20:50:15 by lolaparr          #+#    #+#             */
/*   Updated: 2023/10/17 20:50:15 by lolaparr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_free_double_tab(char **str, int n)
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
