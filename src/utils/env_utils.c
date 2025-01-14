/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lolaparr <lolaparr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 20:09:02 by lolaparr          #+#    #+#             */
/*   Updated: 2023/10/16 20:09:02 by lolaparr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	compare_env_variable(char *new_str, char *env)
{
	char	*tmp;
	int		x;

	tmp = ft_strjoin(new_str, "=");
	if (!tmp)
		return (0);
	x = ft_strncmp(tmp, env, ft_strlen(tmp));
	free(tmp);
	return (!x);
}

char	**new_env(char **env)
{
	int		i;
	int		len;
	char	**new_env;

	i = -1;
	len = double_tab_len(env);
	new_env = ft_calloc(len + 1, sizeof(char *));
	if (!new_env)
		return (NULL);
	while (env[++i])
	{
		new_env[i] = ft_strdup(env[i]);
		if (!new_env[i])
			return (free_double_tab(&new_env), env);
	}
	return (new_env);
}

char	*custom_env(char *new_str, char **env)
{
	int	i;

	i = 0;
	if (env && env[i] && new_str)
	{
		while (env[i])
		{
			if (compare_env_variable(new_str, env[i]))
				return (ft_strchr(env[i], '=') + 1);
			i++;
		}
	}
	return (NULL);
}
