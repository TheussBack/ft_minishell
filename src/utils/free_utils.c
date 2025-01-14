/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lolaparr <lolaparr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 20:09:28 by lolaparr          #+#    #+#             */
/*   Updated: 2023/10/16 20:09:28 by lolaparr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_redir(t_redirect *redir)
{
	if (redir)
	{
		if (redir->next)
			free_redir(redir->next);
		redir->next = NULL;
		free(redir->dst_name);
		redir->dst_name = NULL;
		free(redir->here_doc_eof);
		redir->here_doc_eof = NULL;
		free(redir);
	}
}

void	free_double_strings(char *s1, char *s2)
{
	if (s1)
		free(s1);
	if (s2)
		free(s2);
}

void	multi_free(char ***a, char ***b)
{
	if (a)
		free_double_tab(a);
	if (b)
		free_double_tab(b);
	return ;
}

char	*free_and_return_null(char **str)
{
	free_double_tab(&str);
	return (0);
}

char	*free_and_return_str(char **tab, char *str)
{
	free_double_tab(&tab);
	return (str);
}
