/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_builtin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lolaparr <lolaparr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 20:09:37 by lolaparr          #+#    #+#             */
/*   Updated: 2023/10/16 20:09:37 by lolaparr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	compare_strings(char *s1, char *s2)
{
	char	*tmp;

	tmp = convert_to_lower_case(s1);
	if (!ft_strcmp(s2, tmp))
	{
		free(tmp);
		return (1);
	}
	free(tmp);
	return (0);
}

char	*convert_to_lower_case(char *str)
{
	char	*ret;
	int		i;

	i = 0;
	ret = ft_calloc(ft_strlen(str) + 1, sizeof(char));
	if (!ret)
		return (NULL);
	while (str[i])
	{
		ret[i] = ft_tolower(str[i]);
		i++;
	}
	return (ret);
}
