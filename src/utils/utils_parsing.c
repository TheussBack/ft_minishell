/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lolaparr <lolaparr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 20:09:53 by lolaparr          #+#    #+#             */
/*   Updated: 2023/10/16 20:09:53 by lolaparr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*extract_substring(char const *line, unsigned int begin, size_t max_len)
{
	char	*substr;
	size_t	i;
	size_t	len;

	len = ft_strlen(line);
	i = 0;
	if (max_len > len)
		max_len = len;
	if (len <= begin)
		max_len = 0;
	substr = (char *)malloc((len + 1) * sizeof(char));
	if (!line || !substr)
		return (NULL);
	while (i < max_len && line[begin + i])
	{
		substr[i] = line[begin + i];
		i++;
	}
	substr[i] = '\0';
	return (substr);
}

char	*join_str(char *str1, char *str2)
{
	int		len1;
	int		len2;
	char	*new_str;

	len1 = ft_strlen(str1);
	len2 = ft_strlen(str2);
	new_str = ft_calloc(len1 + len2 + 1, sizeof(char));
	if (!new_str)
		return (str1);
	ft_memcpy(new_str, str1, len1);
	ft_memcpy(new_str + len1, str2, len2);
	if (str1)
		free(str1);
	return (new_str);
}

char	**tokenize_arguments(char **tab)
{
	int		j;
	char	**tmp;
	int		i;
	char	**new_tab;

	new_tab = ft_calloc(1, sizeof(char *));
	if (!new_tab)
		return (tab);
	i = 0;
	while (tab[i])
	{
		j = 0;
		tmp = split_string(tab[i], " \t");
		if (tmp)
		{
			while (tmp[j])
				new_tab = add_str_to_tab(new_tab, tmp[j++]);
			free(tmp);
		}
		i++;
	}
	free_double_tab(&tab);
	return (new_tab);
}

char	**split_string(char *str, char *c)
{
	char	**tab;
	int		i;
	int		begin;

	i = 0;
	tab = NULL;
	begin = 0;
	while (str[i])
	{
		if (is_character_in_string(c, str[i])
			&& !uneven_q(str + begin, i - begin))
		{
			if (i != begin)
			{
				tab = add_token_to_result(str, begin, i, tab);
			}
			begin = i + 1;
		}
		i++;
	}
	if (i != begin)
	{
		tab = add_token_to_result(str, begin, i, tab);
	}
	return (tab);
}

int	is_character_in_string(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (c == str[i])
			return (1);
		i++;
	}
	return (0);
}
