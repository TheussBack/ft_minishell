/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hortense <hortense@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 20:08:13 by lolaparr          #+#    #+#             */
/*   Updated: 2025/01/14 15:44:49 by hortense         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <readline/readline.h>
#include <readline/history.h>

static void	handle_heredoc_signal(int sig)
{
	if (sig == SIGINT)
	{
		//rl_replace_line("", 0);
		close(STDIN_FILENO);
		g_exit_code = 130;
	}
}

static int	loop_heredoc(int fd, int stdin_dup, t_redirect *redir)
{
	char	*line;

	while (1)
	{
		signal(SIGINT, handle_heredoc_signal);
		line = readline("> ");
		if (!line || !ft_strcmp(line, redir->here_doc_eof)
			|| g_exit_code == 130)
		{
			dup2(stdin_dup, STDIN_FILENO);
			close(stdin_dup);
			free(line);
			close(fd);
			return (1);
		}
		else
		{
			write(fd, line, ft_strlen(line));
			write(fd, "\n", 1);
			free(line);
		}
	}
}

static int	stop_heredoc(t_redirect *redir)
{
	int		fd;
	int		stdin_dup;

	stdin_dup = dup(STDIN_FILENO);
	fd = open(redir->dst_name, O_WRONLY | O_TRUNC | O_CREAT, 0644);
	if (fd == -1)
		return (1);
	loop_heredoc(fd, stdin_dup, redir);
	return (0);
}

void	start_heredoc(t_cmd *cmds)
{
	t_redirect		*tmp;

	signal(SIGINT, SIG_IGN);
	while (cmds && g_exit_code != 130)
	{
		tmp = cmds->redirect;
		while (tmp && g_exit_code != 130)
		{
			if (tmp->here_doc_eof)
				stop_heredoc(tmp);
			tmp = tmp->next;
		}
		cmds = cmds->next;
	}
}
