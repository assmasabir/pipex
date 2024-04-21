/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils_1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asabir <asabir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 15:51:30 by asabir            #+#    #+#             */
/*   Updated: 2024/04/21 16:29:54 by asabir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	print_error_and_exit(t_params *tpar)
{
	char	*str;

	str = ": No such file or directory\n";
	if (tpar->cmd[0])
		write(2, tpar->cmd[0], ft_strlen(tpar->cmd[0]));
	write(2, ": ", 2);
	write(2, tpar->name_infile, ft_strlen(tpar->name_infile));
	write(2, str, ft_strlen(str));
	exit(EXIT_FAILURE);
}

void	child_process(int **fd, int in_file, int out_file, t_params *tpar)
{
	int	id;

	id = fork();
	if (id == -1)
		exit(-1);
	if (id == 0)
	{
		close_fds(fd, in_file, out_file, tpar->nb_fds);
		if (dup2(out_file, STDOUT_FILENO) == -1)
		{
			perror(NULL);
			exit(EXIT_FAILURE);
		}
		if (dup2(in_file, STDIN_FILENO) == -1)
			print_error_and_exit(tpar);
		execve(tpar->path_cmd, tpar->cmd, tpar->env);
	}
}

void	free_matrice(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}

void	clean_up(t_params *tpar)
{
	free_matrice(tpar->cmd);
	free(tpar->path_cmd);
}

char	**return_cmd_arr(char **path_cmd, char *cmd, char **env)
{
	char	**arr;
	char	*path;

	arr = ft_split(cmd, ' ');
	path = find_path(env);
	if (path == NULL)
		exit(-1);
	if (is_cmd_found(path_cmd, path, arr[0]) == -1)
	{
		if (cmd)
			write(2, cmd, ft_strlen(cmd));
		write(2, ": command not found\n", 20);
	}
	return (arr);
}
