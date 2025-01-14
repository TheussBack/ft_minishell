/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lolaparr <lolaparr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 20:11:56 by lolaparr          #+#    #+#             */
/*   Updated: 2023/10/16 20:11:56 by lolaparr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**export_all(char **env, int size)
{
	char	**env_ascii;
	char	**ret;
	int		i;

	i = 0;
	env_ascii = sort_by_ascii(env);
	ret = ft_calloc(size + 1, sizeof(char *));
	if (!ret)
		return (NULL);
	if (env_ascii)
	{
		while (env_ascii[i])
		{
			env_ascii[i] = add_double_quotes(env_ascii[i]);
			ret[i] = ft_strjoin("declare -x ", env_ascii[i]);
			if (!ret[i])
				return (free_double_tab(&ret), NULL);
			i++;
		}
		free_double_tab(&env_ascii);
	}
	return (ret);
}

char	*handle_exported_variable(char *cmd, int *j, char **env, char **new_var)
{
	char	*place;
	char	*ret;

	ret = NULL;
	if (ft_isalpha(cmd[0]) || (cmd[0] == '_'))
	{
		place = ft_strchr(cmd, '=');
		if (!place && find_variable_index(env, cmd, ft_strlen(cmd)) == -1)
		{
			ret = create_new_variable(cmd, &new_var[*j], *j);
			if (!ret)
				return (NULL);
			(*j)++;
		}
		if (place)
			ret = update_or_add_var(env, cmd, j, new_var);
	}
	return (ret);
}

char	**process_export(char **cmd, char **env, char **new_var)
{
	int		i;
	int		j;
	int		nb_element;
	char	**ret;

	j = 0;
	i = 0;
	if (cmd[0][0] == '-')
		return (handle_invalid_option(cmd), NULL);
	nb_element = create_new_env_variables(cmd, env, &new_var);
	if ((!new_var && nb_element > 0) || nb_element == -1)
		return (g_exit_code = 1, NULL);
	while (j < nb_element || cmd[i])
		if (!handle_exported_variable(cmd[i++], &j, env, new_var))
			return (NULL);
	ret = merge_two_tab(env, new_var);
	free_double_tab(&new_var);
	if (!ret)
		return (NULL);
	return (ret);
}

void	handle_export_command(t_info *init)
{
	init->export = export_variables(&init->cmd[1], init->my_env,
			double_tab_len(init->my_env));
	if (init->export)
	{
		free_double_tab(&init->my_env);
		init->my_env = init->export;
	}
}

char	**export_variables(char **cmd, char **env, int size)
{
	char	**ret;
	char	**new_var;

	new_var = NULL;
	if (!cmd[0])
	{
		ret = export_all(env, size);
		myy_env(ret, cmd, 1);
		return (g_exit_code = 0, free_double_tab(&ret),
			free_double_tab(&new_var), NULL);
	}
	else
	{
		ret = process_export(cmd, env, new_var);
		if (!ret)
			return (NULL);
	}
	return (g_exit_code = 0, ret);
}
