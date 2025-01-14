/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lolaparr <lolaparr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 20:11:52 by lolaparr          #+#    #+#             */
/*   Updated: 2023/10/16 20:11:52 by lolaparr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	put_line_env(char *s1, char *s2)
{
	ft_putstr_fd(s1, 1);
	ft_putstr_fd(s2, 1);
}

static int	check_character(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (1);
		i++;
	}
	return (0);
}

static void	go_on_my_env(char **my_env, int aff)
{
	int	i;

	i = 0;
	if (aff == 1)
	{
		if (my_env[i])
			while (my_env[i])
				put_line_env(my_env[i++], "\n");
	}
	else if (aff == 2)
	{
		if (my_env[i])
		{
			while (my_env[i])
			{
				if (check_character(my_env[i], '=') == 1)
					put_line_env(my_env[i], "\n");
				i++;
			}
		}
	}
}

void	put_error_env(char *s1, char *s2, char *s3)
{
	ft_putstr_fd(s1, 2);
	ft_putstr_fd(s2, 2);
	ft_putstr_fd(s3, 2);
}

int	myy_env(char **env, char **cmd, int type)
{
	int		size;
	char	c;

	size = double_tab_len(cmd);
	if (!type)
		type = 1;
	if (env && size <= 1)
	{
		go_on_my_env(env, type);
		return (0);
	}
	if (cmd[1][0] == '-')
	{
		c = cmd[1][1];
		put_error_env("env: illegal option -- ", &c, "\nusage: env\n");
	}
	else
	{
		put_error_env("env: ", cmd[1], ": No such file or directory\n");
		return (127);
	}
	return (1);
}
