/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrobin <hrobin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 14:50:30 by hrobin            #+#    #+#             */
/*   Updated: 2023/09/29 14:50:30 by hrobin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_arg(t_info *start, char **env)
{
	start->status = 0;
	start->a = true;
	start->my_env = new_env(env);
	start->sortie = -1;
}

t_type	init_type(void)
{
	t_type	type;

	type.flag = start;
	type.buff = NULL;
	type.dquote = 0;
	type.squote = 0;
	type.i = 0;
	type.current_cmd = NULL;
	type.current_redirect = NULL;
	return (type);
}

void	init_struct(t_variables *info)
{
	info->dquote = 0;
	info->squote = 0;
	info->k = 0;
	info->start = 0;
	info->new = NULL;
}
