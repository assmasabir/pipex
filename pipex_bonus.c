/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asabir <asabir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 23:08:47 by asabir            #+#    #+#             */
/*   Updated: 2024/04/12 21:06:44 by asabir           ###   ########.fr       */
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

int is_cmd_found(char **path_cmd, char *str, char *cmd)
{
	char **path;
	char *join;
	char *temp;

	int i;

	i = 0;
	free(*path_cmd);
	path = ft_split(str, ':');
	if (!ft_strchr(cmd, '/'))
	{
		while (str[i])
		{
			temp = ft_strjoin("/", cmd);
			join = ft_strjoin(path[i], temp);	
			if (access(join, F_OK)==0)
			{
				*path_cmd = strdup(join);
				// printf("iscmdfound %s\n", *path_cmd);
				return (0);
			}
			i++;
		}
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

char **return_cmd_arr(char **path_cmd, char *cmd, char **env)
{
    char **arr = ft_split(cmd, ' ');
    char *path;
 
    path = find_path(env);
	if (path == NULL)
		exit(-1);
	if (is_cmd_found(path_cmd, path, arr[0]))
    {
		write(2, "error\n", 6);
        exit(EXIT_FAILURE);
    }
	// printf("returncmdarr %s\n", *path_cmd);
    return (arr);
}


void child_process(int (*fd)[2], int in_file, int out_file, t_params *tpar)
{
    int id;

    id = fork();
	if (id == -1)
		exit(-1);
	
	if (id == 0)
	{
		// ntf("nnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnbbbbbb %d\n", tpar->nb_fds);
		close_fds(fd, in_file, out_file,tpar->nb_fds);
		dup2(out_file, STDOUT_FILENO);
		if (dup2(in_file, STDIN_FILENO) == -1)
			write(2, "error\n", 6);
		// close(out_file);
		execve(tpar->path_cmd, tpar->cmd, NULL);
	} 
}

void manage_pipes(int nb_fd ,char **argv, char **env, t_params *tpar)
{

    int fd[nb_fd+1][2];
    int i;
	char **cmd;
	char *path_cmd;
	
    i = 0;
	path_cmd = NULL;
    while(i < nb_fd)
    {
        if (pipe(fd[i]) == -1)
		    exit(-1);
        i++;
    }
	i = 0;
	
    while(i < nb_fd)
	{
		if(i == 0)
		{
			cmd = return_cmd_arr(&path_cmd, argv[2], env);
			tpar->cmd = ft_cpymatrix(&(tpar->cmd), cmd);			
			tpar->path_cmd = ft_strcpy(&(tpar->path_cmd) , path_cmd);
			fd[nb_fd][0]= open(argv[1], O_RDONLY);
			child_process(fd, fd[nb_fd][0], fd[i][1], tpar);
			free_matrice(cmd);
			free_matrice(tpar->cmd);
			free(tpar->path_cmd);
			path_cmd = NULL;
		}
		if (i == nb_fd-1)
		{
			cmd = return_cmd_arr(&path_cmd, argv[i+3], env);
			tpar->cmd = ft_cpymatrix(&(tpar->cmd), cmd);
			tpar->path_cmd = ft_strcpy(&(tpar->path_cmd) , path_cmd);
			fd[nb_fd][1] = open(argv[nb_fd+3], O_CREAT | O_RDWR | O_TRUNC, 0644);
			child_process(fd, fd[i][0], fd[nb_fd][1], tpar);
			
			free_matrice(cmd);
			free_matrice(tpar->cmd);
			free(tpar->path_cmd);
		}
		if (i != nb_fd-1)
		{
			cmd = return_cmd_arr(&path_cmd, argv[i+3], env);
		
			tpar->cmd = ft_cpymatrix(&(tpar->cmd), cmd);

			tpar->path_cmd = ft_strcpy(&(tpar->path_cmd) , path_cmd);
			child_process(fd, fd[i][0], fd[i+1][1], tpar);
			free_matrice(cmd);
			free_matrice(tpar->cmd);
			free(tpar->path_cmd);
		}
		i++;
	} 
}

int main(int argc, char **argv, char **env)
{
	
	t_params *tpar;
	tpar = malloc(sizeof(t_params));
	tpar->cmd = NULL;
	tpar->path_cmd = NULL;
	tpar->nb_fds = argc-4;
	manage_pipes(tpar->nb_fds, argv, env, tpar);
	free(tpar);
}

