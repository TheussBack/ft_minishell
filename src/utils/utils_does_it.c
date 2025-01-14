/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_does_it.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lolaparr <lolaparr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 20:09:43 by lolaparr          #+#    #+#             */
/*   Updated: 2023/10/16 20:09:43 by lolaparr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	fill_new_redir(t_redirect *ret, t_redirect r)
{
	ret->dst_name = r.dst_name;
	ret->src_fd = r.src_fd;
	ret->open_flag = r.open_flag;
	ret->is_heredoc = r.is_heredoc;
	ret->here_doc_eof = r.here_doc_eof;
	ret->next = r.next;
}

t_cmd	*create_command(t_cmd **cmd, t_cmd c)
{
	t_cmd	*line;
	t_cmd	*tmp;

	line = ft_calloc(1, sizeof(t_cmd));
	if (line)
	{
		line->command = c.command;
		line->redirect = c.redirect;
		line->next = c.next;
		if (cmd)
		{
			tmp = *cmd;
			if (tmp)
			{
				while (tmp->next)
					tmp = tmp->next;
				tmp->next = line;
			}
			else
				*cmd = line;
		}
	}
	return (line);
}

t_node	*create_word(t_node **cmd, t_node new_word)
{
	t_node	*word;
	t_node	*tmp;

	word = ft_calloc(1, sizeof(t_node));
	if (word)
	{
		word->str = new_word.str;
		word->next = new_word.next;
		if (cmd)
		{
			tmp = *cmd;
			if (tmp)
			{
				while (tmp->next)
					tmp = tmp->next;
				tmp->next = word;
			}
			else
				*cmd = word;
		}
	}
	return (word);
}

int	do_heredoc(t_type *type)
{
	char	*doc;
	char	*n;

	n = ft_itoa(type->i);
	if (!n)
		return (0);
	doc = ft_strjoin("./heredoc_", n);
	free(n);
	if (!doc)
		return (0);
	type->current_redirect = do_redirect(&(type->current_cmd->redirect),
			(t_redirect){0, doc, NULL, O_RDONLY, 1, NULL});
	if (!type->current_redirect)
		return (free(doc), 0);
	type->i++;
	type->flag = HereDocEof;
	return (1);
}

t_redirect	*do_redirect(t_redirect **current, t_redirect fill_new)
{
	t_redirect	*new;
	t_redirect	*tmp;

	new = ft_calloc(1, sizeof(t_redirect));
	if (new)
	{
		fill_new_redir(new, fill_new);
		if (current)
		{
			tmp = *current;
			if (tmp)
			{
				while (tmp->next)
					tmp = tmp->next;
				tmp->next = new;
			}
			else
				*current = new;
		}
	}
	return (new);
}
