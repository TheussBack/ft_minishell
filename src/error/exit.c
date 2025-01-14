/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lolaparr <lolaparr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 20:11:29 by lolaparr          #+#    #+#             */
/*   Updated: 2023/10/16 20:11:29 by lolaparr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	close_fds(t_info init)
{
	dup2(init.fds[0], 0);
	close(init.fds[0]);
	dup2(init.fds[1], 1);
	close(init.fds[1]);
	free_double_tab(&init.cmd);
}
