/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asabir <asabir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 23:08:47 by asabir            #+#    #+#             */
/*   Updated: 2024/04/08 18:26:55 by asabir           ###   ########.fr       */
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

int main(int argc, char **argv, char **env)
{
	int fd[2];
	int id1;
	int id2;
	char *path_cmd1 = NULL;
	char *path_cmd2 = NULL;
	(void)argc;
	char *tmp1 = NULL;
	char *tmp2 = NULL;

	char *path;
	char **cmd1 = ft_split(argv[2], ' ');
	char **cmd2 = ft_split(argv[3], ' ');
	path = find_path(env);
	// printf("%s\n", path);
	if (path == NULL)
		exit(-1);
	if (is_cmd_found(&path_cmd1, path, cmd1[0]))
		printf("error");
	if (is_cmd_found(&path_cmd2, path, cmd2[0]))
		printf("error");
	if (pipe(fd) == -1)
		exit(-1);

	tmp1 = ft_strjoin("/", cmd1[0]);
	tmp2 = ft_strjoin("/", cmd2[0]);

	char *ar1[] = {path_cmd1, NULL};
	char *ar2[] = {path_cmd2, cmd2[1], NULL};
	id1 = fork();
	if (id1 == -1)
		exit(-1);
	if (id1 == 0)
	{
		close(fd[0]);
		int file_in = open(argv[1], O_RDONLY);
		dup2(fd[1], STDOUT_FILENO);
		if (dup2(file_in, STDIN_FILENO) == -1)
			write(2, "error\n", 6);
		close(fd[1]);
		close(file_in);

		if (execve(path_cmd1, ar1, env) == -1);
	}
	id2 = fork();
	if (id2 == -1)
		exit(-1);
	if (id2 == 0)
	{
		close(fd[1]);
		int file_out = open(argv[4], O_CREAT | O_RDWR | O_TRUNC, 0644);
		if (file_out == -1)
			write(2, "error\n", 6);
		if (dup2(fd[0], STDIN_FILENO) == -1)
			write(2, "error\n", 6);
		if (dup2(file_out, STDOUT_FILENO) == -1)
			write(2, "error\n", 6);
		close(file_out);
		close(fd[0]);
		execve(path_cmd2, ar2, env);
	}
	close(fd[0]);
	close(fd[1]);
	wait(NULL);
	wait(NULL);
}