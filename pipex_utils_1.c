/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils_1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asabir <asabir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 15:51:30 by asabir            #+#    #+#             */
/*   Updated: 2024/04/16 23:50:34 by asabir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void child_process(int (*fd)[2], int in_file, int out_file, t_params *tpar)
{
    int id;
	char *str;
	
	str = ": No such file or directory\n";
    id = fork();
	if (id == -1)
		exit(-1);
	
	if (id == 0)
	{
		close_fds(fd, in_file, out_file,tpar->nb_fds);
		dup2(out_file, STDOUT_FILENO);
		if (dup2(in_file, STDIN_FILENO) == -1)
		{
			if(tpar->cmd[0])
				write(2, tpar->cmd[0], ft_strlen(tpar->cmd[0]));
			write(2, ": ", 2);
			write(2, tpar->name_infile, ft_strlen(tpar->name_infile));
			write(2, str, ft_strlen(str));
			exit(EXIT_FAILURE);
		}
		close(out_file);
		close(in_file);
		execve(tpar->path_cmd, tpar->cmd, tpar->env);
	} 
}

void free_matrice(char **str)
{
    int i;

    i = 0;
    while(str[i])
    {
        free(str[i]);
        i++;
    }
    free(str);
}

void clean_up(t_params * tpar)
{

	free_matrice(tpar->cmd);
	
	free(tpar->path_cmd);
}

char **return_cmd_arr(char **path_cmd, char *cmd, char **env)
{
    char **arr = ft_split(cmd, ' ');
    char *path;
    path = find_path(env);
	if (path == NULL)
		exit(-1);
	if (is_cmd_found(path_cmd, path, arr[0])== -1)
    {
		if(cmd)
			write(2, cmd ,ft_strlen(cmd));
		write(2, ": command not found\n", 20);
    }
    return (arr);
}