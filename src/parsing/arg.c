/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lolaparr <lolaparr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 20:08:31 by lolaparr          #+#    #+#             */
/*   Updated: 2023/10/16 21:10:58 by lolaparr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	set_node(char **to_fill, char **begin, char **pos, char *cmd)
{
	*to_fill = NULL;
	*begin = cmd;
	*pos = ft_strchr(cmd, '$');
}

static void	sub_env_var(int *k, char *pos, char **tmp, char **env)
{
	char	*new_str;

	if (pos[*k] != '?')
	{
		if ((ft_isalpha(pos[*k]) || pos[*k] == '_'))
			(*k)++;
		while ((ft_isalnum(pos[*k]) || pos[*k] == '_'))
			(*k)++;
		new_str = extract_substring(pos, 1, *k - 1);
		if ((!new_str || !ft_strlen(new_str))
			&& (pos[*k] == ' ' || pos[*k] == '\0'))
			*tmp = join_str(*tmp, "$");
		else
			*tmp = join_str(*tmp, custom_env(new_str, env));
		free(new_str);
	}
}

static void	proc_n_store_str(char *start, char **tmp, char **cmd, int *i)
{
	char	*s2;

	s2 = extract_substring(start, 0, ft_strlen(start));
	*tmp = join_str(*tmp, s2);
	free(s2);
	if (*tmp)
	{
		free(cmd[*i]);
		cmd[*i] = *tmp;
	}
	(*i)++;
}

char	**process_command_arguments(char **cmd, char **env, int exit_code)
{
	int		i;
	int		j;
	char	*begin;
	char	*to_fill;
	char	*pos;

	i = 0;
	while (cmd[i])
	{
		set_node(&to_fill, &begin, &pos, cmd[i]);
		while (pos)
		{
			if (one_squote(cmd[i], pos - cmd[i]))
				pos = ft_strchr(pos + 1, '$');
			else
			{
				j = sub_var_in_str(&to_fill, exit_code, pos, begin);
				sub_env_var(&j, pos, &to_fill, env);
				begin = pos + j;
				pos = ft_strchr(pos + 1, '$');
			}
		}
		proc_n_store_str(begin, &to_fill, cmd, &i);
	}
	return (cmd);
}

int	sub_var_in_str(char **tmp, int exit_code, char *place, char *start)
{
	char	*tmp2;
	int		k;

	tmp2 = extract_substring(start, 0, place - start);
	*tmp = join_str(*tmp, tmp2);
	free (tmp2);
	k = 1;
	if (place[k] == '?')
	{
		tmp2 = ft_itoa(exit_code);
		*tmp = join_str(*tmp, tmp2);
		free(tmp2);
		k++;
	}
	return (k);
}
