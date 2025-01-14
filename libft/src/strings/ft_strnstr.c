/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lolaparr <lolaparr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 20:51:58 by lolaparr          #+#    #+#             */
/*   Updated: 2023/10/17 20:51:58 by lolaparr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *hay, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;

	j = 0;
	i = 0;
	if (!(*needle))
		return ((char *)hay);
	while (hay[i] && i < len)
	{
		j = 0;
		if (hay[i + j] == needle[j])
		{
			while (hay[i + j] && needle[j] && (i + j) < len
				&& hay[i + j] == needle[j])
				j++;
			if (!(needle[j]))
				return ((char *)&hay[i]);
		}
		i++;
	}
	return (NULL);
}
