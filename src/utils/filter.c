/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filter.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lolaparr <lolaparr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 20:09:22 by lolaparr          #+#    #+#             */
/*   Updated: 2023/10/16 20:09:22 by lolaparr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**filter_out_empty_strings(char **cmd)
{
	int		i;
	char	**new_tab;

	i = 0;
	new_tab = ft_calloc(1, sizeof(char *));
	if (!new_tab)
		return (cmd);
	if (cmd)
	{
		while (cmd[i])
		{
			if (ft_strcmp(cmd[i], ""))
				new_tab = add_str_to_tab(new_tab, cmd[i]);
			else
				free(cmd[i]);
			i++;
		}
	}
	free(cmd);
	return (new_tab);
}
