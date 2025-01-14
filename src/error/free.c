/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lolaparr <lolaparr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 20:11:35 by lolaparr          #+#    #+#             */
/*   Updated: 2023/10/16 20:11:35 by lolaparr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cleanup_heredoc_file(t_cmd *cmd)
{
	t_redirect	*tmp;

	while (cmd)
	{
		tmp = cmd->redirect;
		while (tmp)
		{
			if (tmp->here_doc_eof)
				unlink(tmp->dst_name);
			tmp = tmp->next;
		}
		cmd = cmd->next;
	}
}

void	free_double_tab(char ***str)
{
	int	i;

	i = 0;
	if (!*str)
		return ;
	while ((*str)[i])
	{
		free((*str)[i]);
		(*str)[i] = NULL;
		i++;
	}
	if (*str)
		free(*str);
	*str = NULL;
}

t_cmd	*free_but_not_least(t_cmd *cmd, t_type *type)
{
	free_cmds(cmd);
	free(type->buff);
	return (NULL);
}

void	free_cmds(t_cmd *cmd)
{
	if (cmd)
	{
		if (cmd->next)
			free_cmds(cmd->next);
		cmd->next = NULL;
		free_wrds(cmd->command);
		cmd->command = NULL;
		free_redir(cmd->redirect);
		cmd->redirect = NULL;
		free(cmd);
	}
}

void	free_wrds(t_node *cmd)
{
	if (cmd)
	{
		if (cmd->next)
			free_wrds(cmd->next);
		cmd->next = NULL;
		free(cmd->str);
		cmd->str = NULL;
		free(cmd);
	}
}
