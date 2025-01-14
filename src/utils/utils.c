/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lolaparr <lolaparr@student.42.fr>              +#+  +:+       +#+    */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 15:10:02 by lolaparr            #+#    #+#           */
/*   Updated: 2023/09/29 15:10:02 by lolaparr           ###   ########.fr     */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	end_of_shell(char *str, t_info *start)
{
	ft_putstr_fd(str, 1);
	start->a = false;
}

int	double_tab_len(char **str)
{
	int	i;

	i = 0;
	if (!str || !str[0])
		return (0);
	while (str[i])
		i++;
	return (i);
}

int	nb_cmds(t_cmd *cmds)
{
	int	i;

	i = 0;
	while (cmds)
	{
		++i;
		cmds = cmds->next;
	}
	return (i);
}

char	**add_token_to_result(char *str, int start, int i, char **tab)
{
	char	*tmp;

	tmp = extract_substring(str, start, i - start);
	tab = add_str_to_tab(tab, tmp);
	return (tab);
}

void	put_str_on_stdout(char *str, int i)
{
	ft_putstr_fd(str, 2);
	exit(i);
}
