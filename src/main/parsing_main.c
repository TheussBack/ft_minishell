/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_main.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lolaparr <lolaparr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 20:11:03 by lolaparr          #+#    #+#             */
/*   Updated: 2023/10/16 20:16:54 by lolaparr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_info	init_parsing(t_info start)
{
	if (ft_strlen(start.line))
		add_history(start.line);
	start.commandes = check_quotes(start.line);
	start.tmp = start.commandes;
	start.commandes = typo(start.commandes);
	start.size = nb_cmds(start.commandes);
	start_heredoc(start.commandes);
	start.j = 0;
	return (start);
}

t_info	main_parsing(t_info start)
{
	start.cmd = process_command_arguments(start.cmd, start.my_env, g_exit_code);
	start.cmd = tokenize_arguments(start.cmd);
	start.cmd = filter_out_empty_strings(start.cmd);
	start.cmd = trim_quotes_from_array(start.cmd);
	setup_pipeline(start.j == 0, !start.commandes->next, &start.sortie);
	start.cmd = custom_redir(start.commandes->redirect, start.cmd);
	return (start);
}
