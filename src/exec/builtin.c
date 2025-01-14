/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lolaparr <lolaparr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 20:11:19 by lolaparr          #+#    #+#             */
/*   Updated: 2023/10/16 20:11:19 by lolaparr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	update_env_export(char **cmd, char **env, char *path_env)
{
	char	**export;

	export = export_variables(&cmd[1], env, double_tab_len(env));
	if (export)
	{
		free_double_tab(&env);
		env = export;
		multi_free(&export, &env);
	}
	return (free(path_env), g_exit_code);
}

int	is_builtin(char **cmd, char **env, char *pwd, char *path_env)
{
	if (compare_strings(cmd[0], "cd"))
		return (free(path_env), my_cd(cmd, env, pwd));
	else if (compare_strings(cmd[0], "pwd"))
		return (free(path_env), my_pwd(pwd));
	else if (compare_strings(cmd[0], "env"))
		return (free(path_env), myy_env(env, cmd, 2));
	else if (!ft_strcmp(cmd[0], "exit"))
		ft_putstr_fd("exit\n", 1);
	else if (compare_strings(cmd[0], "unset"))
	{
		env = my_unset(env, &cmd[1]);
		if (!env)
			ft_putstr_fd("Erreur fonction unset\n", 2);
		return (free(path_env), g_exit_code);
	}
	else if (compare_strings(cmd[0], "export"))
		return (update_env_export(cmd, env, path_env));
	else if (compare_strings(cmd[0], "echo"))
		return (free(path_env), my_echo(&cmd[1], env));
	return (-1);
}
