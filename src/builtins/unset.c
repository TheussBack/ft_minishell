/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lolaparr <lolaparr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 20:12:05 by lolaparr          #+#    #+#             */
/*   Updated: 2023/10/16 20:12:05 by lolaparr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	unset_error(char **cmd)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd("unset: -", 2);
	write(2, &cmd[0][1], 1);
	ft_putstr_fd(": invalid option\nunset: usage: unset [name ...]\n", 2);
	g_exit_code = 2;
}

static int	in_the_env(char **cmd, char *env)
{
	int	len;
	int	j;

	j = 0;
	while (cmd[j])
	{
		len = ft_strlen(cmd[j]);
		if (!ft_strncmp(cmd[j], env, len))
			return (1);
		j++;
	}
	return (0);
}

static int	new_size_env(char **cmd, char **env)
{
	int	i;
	int	size;

	size = double_tab_len(env);
	i = 0;
	if (env[i])
	{
		while (env[i] && size)
		{
			if (in_the_env(cmd, env[i]))
				size--;
			i++;
		}
	}
	return (size);
}

static void	unset_var(char **cmd, char **env, char ***new_env)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (env[i])
	{
		if (!in_the_env(cmd, env[i]))
		{
			(*new_env)[j] = ft_strdup(env[i]);
			if (!(*new_env)[j])
			{
				free_double_tab(new_env);
			}
			j++;
		}
		i++;
	}
	g_exit_code = 0;
	free_double_tab(&env);
}

char	**my_unset(char **env, char **cmd)
{
	char	**new_env;
	int		i;

	i = 0;
	new_env = ft_calloc(new_size_env(cmd, env) + 1, sizeof(char *));
	if (!new_env)
		return (NULL);
	if (cmd[i] && env)
	{
		if (cmd[0][0] == '-')
			unset_error(cmd);
		else if ((!ft_isalpha(cmd[0][0]) && !(cmd[0][0] == '_'))
			|| ft_strchr(cmd[0], '='))
			export_display_erreur(cmd[0], 1);
		else
		{
			unset_var(cmd, env, &new_env);
			return (new_env);
		}
	}
	free_double_tab(&new_env);
	return (env);
}
