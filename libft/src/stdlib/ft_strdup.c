/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lolaparr <lolaparr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 20:46:15 by lolaparr          #+#    #+#             */
/*   Updated: 2023/10/17 20:46:15 by lolaparr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*ret;

	ret = ft_calloc((ft_strlen(s1) + 1), sizeof(char));
	if (!ret)
		return (NULL);
	ret = ft_memcpy(ret, s1, ft_strlen(s1));
	return (ret);
}
