/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   does_it.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lolaparr <lolaparr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 20:08:38 by lolaparr          #+#    #+#             */
/*   Updated: 2023/10/16 20:08:38 by lolaparr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	does_it_parse(t_cmd **cmd, t_type *type, char *line)
{
	if (!does_it_command(cmd, type))
		return (0);
	if ((!(type->squote % 2) && !(type->dquote % 2)
			&& search_char(type->c, " \t\n|<>")) || type->c == '\0')
	{
		if (!does_it_word(type))
			return (0);
		if (!does_it_redirect(type, line))
			return (0);
		if (type->c == '|' || type->c == '\0' || type->c == '\n')
			type->flag = start;
	}
	else
	{
		type->buff = do_new_buff(type->buff, type->c);
		if (!type->buff)
			return (0);
	}
	return (1);
}

int	does_it_command(t_cmd **cmd, t_type *type)
{
	if (type->flag == start)
	{
		type->current_cmd = create_command(cmd,
				(t_cmd){NULL, NULL, NULL});
		type->flag = None;
	}
	if (!type->current_cmd)
		return (0);
	return (1);
}

int	does_it_word(t_type *type)
{
	if (type->buff)
	{
		if (type->flag == RedirectName)
			type->current_redirect->dst_name = type->buff;
		else if (type->flag == HereDocEof)
			type->current_redirect->here_doc_eof = type->buff;
		else
		{
			if (!create_word(&(type->current_cmd->command),
					(t_node){type->buff, NULL}))
				return (0);
		}
		type->buff = NULL;
		type->flag = None;
	}
	return (1);
}

int	does_it_redirect(t_type *type, char *str)
{
	if (type->c == '<' || type->c == '>')
	{
		if (!ft_strncmp(str + type->i, "<<", 2))
		{
			if (!do_heredoc(type))
				return (0);
		}
		else
		{
			if (!how_to_redir(type, str))
				return (0);
		}
	}
	return (1);
}

int	how_to_redir(t_type *type, char *str)
{
	if (!ft_strncmp(str + type->i, ">>", 2))
	{
		type->current_redirect = do_redirect(&(type->current_cmd->redirect),
				(t_redirect){1, NULL, NULL, O_CREAT | O_APPEND | O_WRONLY,
				0, NULL});
		type->flag = RedirectName;
		type->i++;
	}
	else if (!ft_strncmp(str + type->i, "<", 1))
	{
		type->current_redirect = do_redirect(&(type->current_cmd->redirect),
				(t_redirect){0, NULL, NULL, O_RDONLY, 0, NULL});
		type->flag = RedirectName;
	}
	else if (!ft_strncmp(str + type->i, ">", 1))
	{
		type->current_redirect = do_redirect(&(type->current_cmd->redirect),
				(t_redirect){1, NULL, NULL, O_CREAT | O_TRUNC | O_WRONLY,
				0, NULL});
		type->flag = RedirectName;
	}
	if (!type->current_redirect)
		return (0);
	return (1);
}
