/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asabir <asabir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 23:08:47 by asabir            #+#    #+#             */
/*   Updated: 2024/04/10 13:43:34 by asabir           ###   ########.fr       */
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
				return (0);
			}
			i++;
		}
	}
	return (-1);
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
    return (arr);
}

void child_process(int in_file, int out_file, char *path_cmd, char **cmd_arr)
{
    int id;

    id = fork();
	if (id == -1)
		exit(-1);
	if (id == 0)
	{
		dup2(out_file, STDOUT_FILENO);
		if (dup2(in_file, STDIN_FILENO) == -1)
			write(2, "error\n", 6);
        
		execve(path_cmd, cmd_arr, NULL);
	} 
}

int main(int argc, char **argv, char **env)
{
	int fd[2];

	char *path_cmd1 = NULL;
	char *path_cmd2 = NULL;
	(void)argc;



	char **cmd1 = return_cmd_arr(&path_cmd1, argv[2], env);
	char **cmd2 = return_cmd_arr(&path_cmd2, argv[3], env);

	if (pipe(fd) == -1)
		exit(-1);

	int file_in = open(argv[1], O_RDONLY);
	child_process(file_in, fd[1], path_cmd1, cmd1);
    close(file_in);
	
	int file_out = open(argv[4], O_CREAT | O_RDWR | O_TRUNC, 0644);
	close(fd[1]);
	child_process(fd[0], file_out, path_cmd2, cmd2);
    close(file_out);
	
	close(fd[0]);
	
	wait(NULL);
	wait(NULL);
}