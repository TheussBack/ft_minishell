/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lolaparr <lolaparr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 20:11:16 by lolaparr          #+#    #+#             */
/*   Updated: 2023/10/16 20:11:16 by lolaparr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	setup_pipeline(int begin, int end, int *strout)
{
	int	pfd[2];

	if (!begin)
	{
		dup2(*strout, 0);
		close(*strout);
	}
	if (!end)
	{
		if (pipe(pfd) == -1)
			ft_putstr_fd("Erreur pipe\n", 2);
		else
		{
			dup2(pfd[1], 1);
			close(pfd[1]);
			*strout = pfd[0];
		}
	}
}

/*In summary, the ft_putstr_fd function takes a string as input and
outputs its characters one by one to the specified file descriptor fd.
This function is similar to the standard library function write(), but
it processes a string character by character and relies on another function
(ft_putchar_fd) to perform the actual output.*/

char	**custom_redir(t_redirect *cmd, char **tab)
{
	int	fd;

	while (cmd)
	{
		if (cmd->dst_name)
		{
			fd = open(cmd->dst_name, cmd->open_flag, 0644);
			if (fd == -1)
			{
				ft_putstr_fd("minishell: ", 2);
				ft_putstr_fd(cmd->dst_name, 2);
				ft_putstr_fd(": ", 2);
				perror("");
				free_double_tab(&tab);
				g_exit_code = 2;
				return (NULL);
			}
			dup2(fd, cmd->src_fd);
			close(fd);
		}
		cmd = cmd->next;
	}
	return (tab);
}

int	child_process(char **cmd, char **env, char *path_env, int sortie)
{
	char	pwd[2048];
	char	*path_cmd;

	getcwd(pwd, 2048);
	if (is_builtin(cmd, env, pwd, path_env) != -1)
		return (g_exit_code);
	else
	{
		if (sortie != -1)
			close(sortie);
		path_cmd = find_executable_path(cmd, path_env);
		execve(path_cmd, cmd, env);
		ft_putstr_fd("minishell: ", 2);
		if (errno == ENOENT)
			return (command_not_found_error(cmd, path_env));
		if (errno == EACCES)
			return (command_execution_error(cmd, path_env, path_cmd));
		return (free(path_env), perror(cmd[0]), -1);
	}
	return (-1);
}

int	command_execution_error(char **cmd, char *path_env, char *new_cmd)
{
	if (!path_env || ft_strlen(path_env) == 0)
		return (free(path_env), perror(cmd[0]), 127);
	perror(cmd[0]);
	if (!ft_strcmp(cmd[0], "..") || !ft_strcmp(cmd[0], ".")
		|| !ft_strncmp(cmd[0], "../", 3))
		free_double_strings(new_cmd, path_env);
	else
		free(path_env);
	return (126);
}

int	find_path_variable_index(char **env)
{
	int	i;

	i = -1;
	if (!env)
		return (0);
	while (env[++i])
	{
		if (!ft_strncmp(env[i], "PATH=", 5))
			return (i);
	}
	return (0);
}
