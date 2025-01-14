/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lolaparr <lolaparr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 20:09:08 by lolaparr          #+#    #+#             */
/*   Updated: 2023/10/16 20:09:08 by lolaparr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	export_display_erreur(char *cmd, int nb)
{
	ft_putstr_fd("minishell: ", 2);
	if (nb == 0)
		ft_putstr_fd("export: `", 2);
	if (nb == 1)
		ft_putstr_fd("unset: `", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd("': not a valid identifier\n", 2);
	g_exit_code = 1;
}

void	handle_invalid_option(char **cmd)
{
	ft_putstr_fd("minishell: export: -", 2);
	write(2, &cmd[0][1], 1);
	ft_putstr_fd(": invalid option\n", 2);
	ft_putstr_fd("export: usage: export [name[=value] ...]\n", 2);
	g_exit_code = 2;
}

int	create_new_env_variables(char **cmd, char **env, char ***new_var)
{
	int	nb_element;

	nb_element = verify_and_count_new_variables(cmd, env);
	if (nb_element == -1)
		return (-1);
	if (nb_element)
		*new_var = ft_calloc(nb_element + 1, sizeof(char *));
	return (nb_element);
}

int	find_variable_index(char **env, char *var, int place)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (!ft_strncmp(env[i], var, place))
			return (i);
		i++;
	}
	return (-1);
}

void	display_error(char *cmd, int nb)
{
	ft_putstr_fd("minishell: ", 2);
	if (nb == 0)
		ft_putstr_fd("export: `", 2);
	if (nb == 1)
		ft_putstr_fd("unset: `", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd("': not a valid identifier\n", 2);
	g_exit_code = 1;
}
