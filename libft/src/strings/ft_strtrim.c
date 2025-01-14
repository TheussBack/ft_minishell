/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lolaparr <lolaparr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 20:52:05 by lolaparr          #+#    #+#             */
/*   Updated: 2023/10/17 20:52:05 by lolaparr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_intheset(char c, char const *set)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (c == set[i])
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*ret;
	int		start;
	int		size;

	if (!s1 || !set)
		return (NULL);
	size = ft_strlen(s1);
	start = 0;
	while (s1[start] && ft_intheset(s1[start], set))
		start++;
	while ((size > start) && ft_intheset(s1[size - 1], set))
		size--;
	ret = ft_calloc((size - start + 1), sizeof(char));
	if (!ret)
		return (NULL);
	ft_memcpy(ret, &s1[start], (size - start));
	return (ret);
}
