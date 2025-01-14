/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lolaparr <lolaparr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 20:09:48 by lolaparr          #+#    #+#             */
/*   Updated: 2023/10/16 20:09:48 by lolaparr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_valid_command(char *cmd)
{
	int	res;

	res = 0;
	res = ft_strncmp(cmd, "./", 2);
	if (res == 0)
		return (res);
	res = ft_strcmp(cmd, """");
	return (res);
}

char	*find_executable_path(char **cmd, char *path_env)
{
	char	**new_path;
	char	*tmp;
	int		i;

	i = -1;
	if (!path_env)
		put_str_on_stdout("minishell: No such file or directory\n", 127);
	if ((cmd[0][0]) != '/' && is_valid_command(cmd[0]) != 0)
	{
		new_path = split_path_env(path_env);
		while (new_path[++i])
		{
			tmp = ft_calloc(sizeof(char), (ft_strlen(new_path[i])
						+ ft_strlen(cmd[0]) + 2));
			if (!tmp)
				return (free_and_return_null(new_path));
			tmp = ft_strcat_multiple(tmp, new_path[i], "/", cmd[0]);
			if (access(tmp, X_OK) == 0)
				return (free_and_return_str(new_path, tmp));
			free(tmp);
		}
		if (new_path)
			free_double_tab(&new_path);
	}
	return (cmd[0]);
}

/*En résumé, cette fonction prend un nom de fichier
(ou de commande) potentiellement relatif et le chemin
d'accès d'un répertoire, et elle essaie de trouver le chemin
d'accès absolu complet du fichier en concaténant le chemin du répertoire
avec le nom du fichier. Si elle trouve un chemin d'accès absolu exécutable,
elle le retourne. Sinon, elle retourne le nom du fichier d'origine.*/

char	**split_path_env(char *path)
{
	char	**new_path;

	if (ft_strchr(path, '='))
		new_path = ft_split(ft_strchr(path, '=') + 1, ':');
	else
		new_path = ft_split(path, ':');
	return (new_path);
}

char	*ft_strcat_multiple(char *dest, char *a, char *b, char *c)
{
	dest = ft_strcat(dest, a);
	dest = ft_strcat(dest, b);
	dest = ft_strcat(dest, c);
	return (dest);
}

int	command_not_found_error(char **cmd, char *path_env)
{
	if (!ft_strchr(cmd[0], '/'))
	{
		ft_putstr_fd(cmd[0], 2);
		ft_putstr_fd(": command not found\n", 2);
	}
	else
		perror(cmd[0]);
	free(path_env);
	return (127);
}
