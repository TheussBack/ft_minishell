/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lolaparr <lolaparr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 20:08:47 by lolaparr          #+#    #+#             */
/*   Updated: 2023/10/16 20:08:47 by lolaparr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd	*check_quotes(char *line)
{
	t_cmd		*cmd;
	t_type		type;

	cmd = NULL;
	type = init_type();
	while (type.i <= ft_strlen(line))
	{
		type.c = line[type.i];
		if (type.c == '\"' && !(type.squote % 2)
			&& (ft_strchr(line + type.i + 1, '\"') || type.dquote % 2))
			type.dquote++;
		if (type.c == '\'' && !(type.dquote % 2)
			&& (ft_strchr(line + type.i + 1, '\'') || type.squote % 2))
			type.squote++;
		if (!does_it_parse(&cmd, &type, line))
			return (free_but_not_least(cmd, &type));
		type.i++;
	}
	return (cmd);
}

t_cmd	*typo(t_cmd *cmd)
{
	t_cmd		*tmp;
	int			nb;

	tmp = cmd;
	nb = nb_cmds(cmd);
	if (nb > 1)
	{
		while (tmp)
		{
			if (!tmp->command)
			{
				ft_putstr_fd("minishell: syntax error\n", 2);
				return (NULL);
			}
			tmp = tmp->next;
		}
	}
	if (!has_typo_error(cmd))
		return (NULL);
	return (cmd);
}

int	search_char(char c, const char *str)
{
	int	i;

	i = 0;
	if (str)
	{
		while (str[i])
		{
			if (c == str[i])
				return (1);
			i++;
		}
	}
	return (0);
}
