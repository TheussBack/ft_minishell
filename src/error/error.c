/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lolaparr <lolaparr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 20:11:26 by lolaparr          #+#    #+#             */
/*   Updated: 2023/10/16 20:13:18 by lolaparr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd	*has_typo_error(t_cmd *cmds)
{
	t_redirect	*tmp_redir;
	t_cmd		*tmp;

	tmp = cmds;
	while (tmp)
	{
		tmp_redir = tmp->redirect;
		while (tmp_redir)
		{
			if (!tmp_redir->dst_name
				|| (tmp_redir->is_heredoc && !tmp_redir->here_doc_eof))
			{
				ft_putstr_fd("minishell: syntax error\n", 2);
				g_exit_code = 2;
				return (NULL);
			}
			tmp_redir = tmp_redir->next;
		}
		tmp = tmp->next;
	}
	return (cmds);
}
