/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrobin <hrobin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 14:11:54 by hrobin            #+#    #+#             */
/*   Updated: 2023/09/29 14:11:54 by hrobin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_exit_code = 0;

void	manage_loop(t_info *start)
{
	*start = init_parsing(*start);
	while (start->commandes && start->a)
	{
		start->fds[0] = dup(0);
		start->fds[1] = dup(1);
		start->cmd = do_tab(start->commandes->command);
		if (start->cmd)
		{
			*start = main_parsing(*start);
			if (start->cmd && start->cmd[0])
				builtin_main(start);
			close_fds(*start);
		}
		start->j++;
		start->commandes = start->commandes->next;
	}
	cleanup_heredoc_file(start->tmp);
	free_cmds(start->tmp);
	free(start->line);
	start->line = NULL;
}

static	void	start_shell(t_info *start)
{
	while (start->a)
	{
		getcwd(start->pwd, 2048);
		signal_boss();
		start->line = readline("minishell $> ");
		if (!isatty(0))
			start->a = 0;
		if (!start->line || !isatty(0))
			end_of_shell("exit\n", start);
		if (start->line)
			manage_loop(start);
		while (waitpid(-1, &start->status, 0) != -1)
		{
			if (WIFSIGNALED(start->status))
				handle_signal(WTERMSIG(start->status));
			else if (WIFEXITED(start->status))
				g_exit_code = WEXITSTATUS(start->status);
		}
	}
}

int	main(int ac, char **av, char **env)
{
	t_info	start;

	(void)ac;
	(void)av;
	init_arg(&start, env);
	if (!start.my_env)
		return (0);
	start_shell(&start);
	return (free_double_tab(&start.my_env), g_exit_code);
}
