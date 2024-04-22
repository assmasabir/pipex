/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asabir <asabir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 23:55:14 by asabir            #+#    #+#             */
/*   Updated: 2024/04/22 20:31:11 by asabir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*find_path(char **en)
{
	int	i;

	i = 0;
	while (en[i])
	{
		if (strncmp(en[i], "PATH=", 5) == 0)
			return (en[i]);
		else
			i++;
	}
	return (NULL);
}

void	free_all(char *temp, char *join, char **path, char **path_cmd)
{
	*path_cmd = ft_strdup(join);
	free(temp);
	free(join);
	free_matrice(path);
}

void	free_all2(char *temp, char *join)
{
	free(temp);
	free(join);
}

int	search_for_cmd(char **path_cmd, char **path, char *cmd)
{
	char	*temp;
	int		i;
	char	*join;

	i = 0;
	while (path[i])
	{
		temp = ft_strjoin("/", cmd);
		join = ft_strjoin(path[i], temp);
		if (access(join, F_OK | X_OK) == 0)
		{
			free_all(temp, join, path, path_cmd);
			return (0);
		}
		free_all2(temp, join);
		i++;
	}
	return (-1);
}

int	is_cmd_found(char **path_cmd, char *str, char *cmd)
{
	char	**path;
	int		i;

	i = 1;
	path = ft_split(str, ':');
	if (!ft_strchr(cmd, '/'))
	{
		i = search_for_cmd(path_cmd, path, cmd);
		if (i == 0)
			return (0);
		free_matrice(path);
	}
	else if (!access(cmd, F_OK | X_OK))
	{
		*path_cmd = ft_strdup(cmd);
		free_matrice(path);
		return (0);
	}
	else
		free_matrice(path);
	return (-1);
}
