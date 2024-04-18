/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asabir <asabir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 23:55:14 by asabir            #+#    #+#             */
/*   Updated: 2024/04/16 18:30:04 by asabir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char *find_path(char **en)
{
	int i = 0;
	while (en[i])
	{
		if (strncmp(en[i], "PATH=", 5) == 0)
			return (en[i]);
		else
			i++;
	}
	return (NULL);
}

int ft_strcmp(char *s1, char *s2)
{
	int i;
	
	i = 0;
	if(s1==NULL || s2 == NULL)
		return(-1);
	while(s1[i] != '\0' && s2[i] != '\0' && s1[i]==s2[i])
	{
		i++;
	}
	return(s1[i]-s2[i]);
}


int is_cmd_found(char **path_cmd, char *str, char *cmd)
{
	char **path;
	char *join;
	char *temp;
	int i;

	i = 0;
	join = "NULlL";
	path = ft_split(str, ':');
	if (!ft_strchr(cmd, '/'))
	{
		while(path[i])
		{
			temp = ft_strjoin("/", cmd);
			join = ft_strjoin(path[i], temp);	
			if (access(join, F_OK)==0)
			{
				*path_cmd = ft_strdup(join);
				free(temp);
				free(join);
				free_matrice(path);
				return (0);
			}
			i++;
			free(temp);
			free(join);
		}
	free_matrice(path);
	}
	return (-1);
}

void close_fds(int (*fd)[2], int file_in, int file_out, int nb_fds)
{
    int i;

    i = 0;
	while(i <= nb_fds)
	{
		if(fd[i][0] == file_in || fd[i][1] == file_out)
		{
			if(fd[i][0] == file_in)
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
