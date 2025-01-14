/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gestion_memory.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lolaparr <lolaparr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 20:09:32 by lolaparr          #+#    #+#             */
/*   Updated: 2023/10/16 20:09:32 by lolaparr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*do_new_buff(char *old_buff, char c)
{
	int		size;
	char	*new_buff;

	size = 2;
	if (old_buff)
		size += ft_strlen(old_buff);
	new_buff = ft_calloc(size, sizeof(char));
	if (new_buff)
	{
		if (old_buff)
			ft_memmove(new_buff, old_buff, ft_strlen(old_buff) * sizeof(char));
		new_buff[ft_strlen(new_buff)] = c;
	}
	if (old_buff)
		free(old_buff);
	return (new_buff);
}

char	**merge_two_tab(char **dptr1, char **dptr2)
{
	char	**ret;
	int		len1;
	int		len2;
	int		i;

	i = 0;
	len1 = double_tab_len(dptr1);
	len2 = double_tab_len(dptr2);
	ret = ft_calloc(1, sizeof(char *));
	if (!ret)
		return (NULL);
	while (i < len1)
	{
		ret = add_str_to_tab(ret, ft_strdup(dptr1[i]));
		i++;
	}
	i = 0;
	while (i < len2)
	{
		ret = add_str_to_tab(ret, ft_strdup(dptr2[i]));
		i++;
	}
	return (ret);
}

char	**add_str_to_tab(char **tab, char *str)
{
	char	**new_tab;
	int		len;

	len = double_tab_len(tab);
	if (str)
		len += 1;
	new_tab = ft_calloc(len + 1, sizeof(char *));
	if (!new_tab)
		return (tab);
	if (tab)
	{
		ft_memmove(new_tab, tab, double_tab_len(tab) * sizeof(char *));
		free(tab);
	}
	if (str)
		ft_memmove(new_tab + double_tab_len(new_tab), &str, sizeof(char *));
	return (new_tab);
}

char	**do_tab(t_node *word)
{
	char	**tab;

	tab = ft_calloc(1, sizeof(char *));
	if (!tab)
		return (NULL);
	while (word)
	{
		tab = add_str_to_tab(tab, ft_strdup(word->str));
		word = word->next;
	}
	return (tab);
}
