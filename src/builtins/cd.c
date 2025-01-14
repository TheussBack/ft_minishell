/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lolaparr <lolaparr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 20:11:41 by lolaparr          #+#    #+#             */
/*   Updated: 2023/10/16 21:12:57 by lolaparr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	cd_display_error(char **cmd)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(cmd[0], 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(cmd[1], 2);
}

static char	**update_old_pwd(char **env, char *new_pwd)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (!ft_strncmp("OLDPWD=", env[i], 7))
		{
			free(env[i]);
			env[i] = ft_strdup(new_pwd);
			if (!env[i])
			{
				free(new_pwd);
				return (NULL);
			}
			break ;
		}
		i++;
	}
	free(new_pwd);
	return (env);
}

static char	**update_pwd(char **env, char *new_pwd)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (!ft_strncmp("PWD=", env[i], 4))
		{
			free(env[i]);
			env[i] = ft_strdup(new_pwd);
			if (!env[i])
			{
				free(new_pwd);
				return (NULL);
			}
			break ;
		}
		i++;
	}
	free(new_pwd);
	return (env);
}

static char	**update_env(char *old_pwd, char **env)
{
	char	*new_pwd;

	new_pwd = ft_calloc(2048 + 5, sizeof(char));
	if (!new_pwd)
		return (NULL);
	ft_memcpy(new_pwd, "PWD=", 4);
	getcwd(&new_pwd[4], 2048);
	if (!update_pwd(env, new_pwd))
		return (NULL);
	new_pwd = NULL;
	new_pwd = ft_calloc(ft_strlen(old_pwd) + 8, sizeof(char));
	if (!new_pwd)
		return (NULL);
	ft_memcpy(new_pwd, "OLDPWD=", 7);
	ft_memcpy(&new_pwd[7], old_pwd, ft_strlen(old_pwd));
	if (!update_old_pwd(env, new_pwd))
		return (NULL);
	return (env);
}

int	my_cd(char **cmd, char **env, char *pwd)
{
	if (cmd[1])
	{
		if (chdir(cmd[1]) != 0)
		{
			cd_display_error(cmd);
			ft_putstr_fd(": ", 2);
			perror("");
		}
		else
		{
			if (!update_env(pwd, env))
				ft_putstr_fd("L'update de l'environnement a echoue", 2);
			else
				return (0);
		}
	}
	return (1);
}
