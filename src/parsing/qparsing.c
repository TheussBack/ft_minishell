/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   qparsing.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+
	+:+     */
/*   By: lolaparr <lolaparr@student.42.fr>          +#+  +:+
	+#+        */
/*                                                +#+#+#+#+#+
	+#+           */
/*   Created: 2023/10/16 20:08:52 by lolaparr          #+#    #+#             */
/*   Updated: 2023/10/16 20:08:52 by lolaparr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	process_quotes_and_concatenate(t_variables *x, char *cmd)
{
	char	*tmp;

	if (cmd[x->k] == '\'' && !(x->dquote % 2) && (ft_strchr(cmd + x->k + 1,
				'\'') || (x->squote % 2)))
	{
		x->squote++;
		tmp = extract_substring(cmd, x->start, x->k - x->start);
		x->new = join_str(x->new, tmp);
		free(tmp);
		x->start = x->k + 1;
	}
	if (cmd[x->k] == '\"' && !(x->squote % 2) && (ft_strchr(cmd + x->k + 1,
				'\"') || (x->dquote % 2)))
	{
		x->dquote++;
		tmp = extract_substring(cmd, x->start, x->k - x->start);
		x->new = join_str(x->new, tmp);
		free(tmp);
		x->start = x->k + 1;
	}
	x->k++;
}

int	one_squote(char *pos, int len)
{
	int	dquote;
	int	squote;
	int	i;

	squote = 0;
	dquote = 0;
	i = 0;
	while (pos[i] && i < len)
	{
		if (pos[i] == '\"' && !(squote % 2) && (ft_strchr(pos + i + 1, '\"')
				|| (dquote % 2)))
			dquote++;
		if (pos[i] == '\'' && !(dquote % 2) && (ft_strchr(pos + i + 1, '\'')
				|| (squote % 2)))
			squote++;
		i++;
	}
	if (!(squote % 2))
		return (0);
	return (1);
}

int	one_dquote(char *pos, int len)
{
	int	squote;
	int	dquote;
	int	i;

	squote = 0;
	dquote = 0;
	i = 0;
	while (pos[i] && i < len)
	{
		if (pos[i] == '\'' && !(dquote % 2) && (ft_strchr(pos + i + 1, '\'')
				|| (squote % 2)))
			squote++;
		if (pos[i] == '\"' && !(squote % 2) && (ft_strchr(pos + i + 1, '\"')
				|| (dquote % 2)))
			dquote++;
		i++;
	}
	if (!(dquote % 2))
		return (0);
	return (1);
}

int	uneven_q(char *pos, int len)
{
	if (one_dquote(pos, len) || one_squote(pos, len))
		return (1);
	return (0);
}

char	**trim_quotes_from_array(char **cmd)
{
	t_variables		x;
	char			*tmp;
	int				i;

	i = 0;
	while (cmd[i])
	{
		init_struct(&x);
		while (cmd[i][x.k])
			process_quotes_and_concatenate(&x, cmd[i]);
		tmp = extract_substring(cmd[i], x.start, x.k - x.start);
		x.new = join_str(x.new, tmp);
		free(tmp);
		if (x.new)
		{
			free(cmd[i]);
			cmd[i] = x.new;
		}
		i++;
	}
	return (cmd);
}
