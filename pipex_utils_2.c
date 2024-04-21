/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asabir <asabir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 23:55:14 by asabir            #+#    #+#             */
/*   Updated: 2024/04/21 15:33:45 by asabir           ###   ########.fr       */
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

int	is_cmd_found(char **path_cmd, char *str, char *cmd)
{
	char	**path;
	char	*join;
	char	*temp;
	int		i;

	i = 0;
	join = "NULlL";
	path = ft_split(str, ':');
	if (!ft_strchr(cmd, '/'))
	{
		while (path[i])
		{
			temp = ft_strjoin("/", cmd);
			join = ft_strjoin(path[i], temp);
			if (access(join, F_OK) == 0)
			{
				free_all(temp, join, path, path_cmd);
				return (0);
			}
			free_all2(temp, join);
			i++;
		}
		free_matrice(path);
	}
	return (-1);
}

void	close_fds(int **fd, int file_in, int file_out, int nb_fds)
{
	int	i;

	i = 0;
	while (i <= nb_fds)
	{
		if (fd[i][0] == file_in || fd[i][1] == file_out)
		{
			if (fd[i][0] == file_in)
			{
				close(fd[i][1]);
				i++;
			}
			else if (fd[i][1] == file_out)
			{
				close(fd[i][0]);
				i++;
			}
		}
		else
		{
			close(fd[i][0]);
			close(fd[i][1]);
			i++;
		}
	}
}
