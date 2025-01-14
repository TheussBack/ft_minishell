/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_variable_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lolaparr <lolaparr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 20:09:13 by lolaparr          #+#    #+#             */
/*   Updated: 2023/10/16 20:09:13 by lolaparr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*update_or_add_var(char **env, char *cmd, int *j, char **new_var)
{
	char	*ret;
	char	*place;

	ret = NULL;
	place = ft_strchr(cmd, '=');
	if (find_variable_index(env, cmd, place - cmd) == -1)
	{
		ret = create_new_variable(cmd, &new_var[*j], *j);
		if (!ret)
			return (NULL);
		(*j)++;
	}
	else
	{
		ret = update_environment_variable(cmd, env, place);
		if (!ret)
			return (NULL);
	}
	return (ret);
}

char	*update_environment_variable(char *cmd, char **env, char *place)
{
	char	*tmp;
	int		index;

	tmp = 0;
	index = 0;
	if (cmd[0] != '_' || cmd[1] != '=')
	{
		index = find_variable_index(env, cmd, place - cmd);
		tmp = env[index];
		env[index] = ft_strdup(cmd);
		free(tmp);
	}
	return (env[index]);
}

int	verify_and_count_new_variables(char **cmd, char **env)
{
	char	*place;
	int		i;
	int		add_new;

	add_new = 0;
	i = 0;
	if (cmd[i])
	{
		while (cmd[i])
		{
			place = ft_strchr(cmd[i], '=');
			if (!place)
				return (1);
			if (!ft_isalpha(cmd[i][0]) && !(cmd[i][0] == '_'))
				return (display_error(cmd[i], 0), -1);
			else
			{
				if (place
					&& find_variable_index(env, cmd[i], place - cmd[i]) == -1)
					add_new++;
			}
			i++;
		}
	}
	return (add_new);
}
