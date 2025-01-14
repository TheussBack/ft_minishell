/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lolaparr <lolaparr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 20:11:09 by lolaparr          #+#    #+#             */
/*   Updated: 2023/10/16 20:11:09 by lolaparr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	builtin_main(t_info *start)
{
	if (compare_strings(start->cmd[0], "cd"))
		g_exit_code = my_cd(start->cmd, start->my_env, start->pwd);
	else if (compare_strings(start->cmd[0], "pwd"))
		g_exit_code = my_pwd(start->pwd);
	else if (compare_strings(start->cmd[0], "env"))
		g_exit_code = myy_env(start->my_env, start->cmd, 2);
	else if (!ft_strcmp(start->cmd[0], "exit"))
	{
		ft_putstr_fd("exit\n", 1);
		if (start->cmd[1] && ft_atoi(start->cmd[1]) <= 255
			&& ft_atoi(start->cmd[1]) >= 0)
			g_exit_code = ft_atoi(start->cmd[1]);
		if (start->size < 2)
			start->a = 0;
	}
	else if (compare_strings(start->cmd[0], "unset"))
		start->my_env = my_unset(start->my_env, &start->cmd[1]);
	else if (compare_strings(start->cmd[0], "export"))
		handle_export_command(start);
	else if (compare_strings(start->cmd[0], "echo"))
		g_exit_code = my_echo(&start->cmd[1], start->my_env);
	else
		run_shell_command(start);
}

void	run_shell_command(t_info *init)
{
	g_exit_code = launch_command_process(init->cmd, init->my_env, init->sortie);
	if (g_exit_code != 256)
	{
		init->a = 0;
		g_exit_code = 127;
	}
}

int	launch_command_process(char **cmd, char **env, int out)
{
	pid_t	pid;
	char	*path_env;
	char	pwd[2048];

	getcwd(pwd, 2048);
	path_env = find_line_path_env(env);
	if (!path_env)
		exit(127);
	pid = fork();
	if (pid == -1)
		perror("fork");
	if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		return (child_process(cmd, env, path_env, out), -1);
	}
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	if (path_env)
		free(path_env);
	return (256);
}

char	*find_line_path_env(char **env)
{
	char	*str;
	int		i;

	i = find_path_variable_index(env);
	str = ft_strdup(env[i]);
	return (str);
}
