/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_very_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lolaparr <lolaparr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 20:09:18 by lolaparr          #+#    #+#             */
/*   Updated: 2023/10/16 20:09:18 by lolaparr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*add_double_quotes(char *env)
{
	char	*ret;
	char	*place;

	place = ft_strchr(env, '=');
	if (place)
	{
		ret = ft_substr(env, 0, (place - env) + 1);
		ret = join_str(ret, "\"");
		ret = join_str(ret, place + 1);
		ret = join_str(ret, "\"");
		free(env);
		return (ret);
	}
	return (env);
}

char	*create_new_variable(char *cmd, char **new_var, int j)
{
	(void)j;
	*new_var = ft_strdup(cmd);
	if (!*new_var)
	{
		free_double_tab(&new_var);
		return (NULL);
	}
	return (*new_var);
}

char	**sort_by_ascii(char **env)
{
	char	**ret;
	char	*tmp;
	int		i;
	int		j;

	i = 0;
	ret = duplicate_environment(env);
	if (!ret)
		return (NULL);
	while (ret[i])
	{
		j = i;
		while (ret[j])
		{
			if (ft_strncmp(ret[i], ret[j], ft_strlen(ret[j])) > 0)
			{
				tmp = ret[i];
				ret[i] = ret[j];
				ret[j] = tmp;
			}
			j++;
		}
		i++;
	}
	return (ret);
}

char	**duplicate_environment(char **env)
{
	char	**ret;
	int		size;
	int		i;

	i = 0;
	size = double_tab_len(env);
	ret = ft_calloc(size + 1, sizeof(char *));
	if (!ret)
		return (NULL);
	while (env[i])
	{
		ret[i] = ft_strdup(env[i]);
		if (!ret[i])
		{
			free_double_tab(&ret);
			return (env);
		}
		i++;
	}
	return (ret);
}
