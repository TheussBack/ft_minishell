/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lolaparr <lolaparr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 20:11:47 by lolaparr          #+#    #+#             */
/*   Updated: 2023/10/16 20:11:47 by lolaparr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	has_multiple_n(char *cmd)
{
	int	i;

	i = 0;
	if (cmd[i] == '-' && cmd[i + 1])
	{
		i++;
		while (cmd[i])
		{
			if (cmd[i] != '\0' && cmd[i] != 'n')
				return (0);
			i++;
		}
	}
	else
		return (0);
	return (1);
}

static void	print_echo(char **cmd, int *new_line)
{
	int	size;
	int	i;

	i = 0;
	size = double_tab_len(cmd);
	while (cmd[i])
	{
		if (has_multiple_n(cmd[i]) && i < size)
		{
			i++;
			*new_line = 0;
		}
		else
			break ;
	}
	if (cmd[i])
	{
		while (cmd[i] && i < size)
		{
			ft_putstr_fd(cmd[i], 1);
			if (i < (size - 1))
				ft_putstr_fd(" ", 1);
			i++;
		}
	}
}

int	my_echo(char **cmd, char **env)
{
	int	new_line;

	(void)env;
	new_line = 1;
	if (cmd[0])
		print_echo(cmd, &new_line);
	if (new_line)
		ft_putstr_fd("\n", 1);
	return (0);
}
