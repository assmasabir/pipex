/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asabir <asabir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 23:08:47 by asabir            #+#    #+#             */
/*   Updated: 2024/04/28 14:12:13 by asabir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	case_1(int **fd, t_params *tpar, char **argv, int *i)
{
	if (tpar->path_cmd)
	{
		free(tpar->path_cmd);
		tpar->path_cmd = NULL;
	}
	if (tpar->here_doc == 1)
	{
		fd[tpar->nb_fds][0] = manage_here_doc(argv);
		close(fd[tpar->nb_fds][0]);
		fd[tpar->nb_fds][0] = open("here_doc", O_RDONLY, 0644);
	}
	else
		fd[tpar->nb_fds][0] = open(argv[1], O_RDONLY);
	tpar->cmd = return_cmd_arr(&(tpar->path_cmd), argv[2], tpar);
	child_process(fd, fd[tpar->nb_fds][0], fd[*i][1], tpar);
	clean_up(tpar);
	tpar->path_cmd = NULL;
	close(fd[tpar->nb_fds][1]);
}

void	case_2(int **fd, t_params *tpar, char **argv, int *i)
{
	if (tpar->path_cmd)
	{
		free(tpar->path_cmd);
		tpar->path_cmd = NULL;
	}
	tpar->cmd = return_cmd_arr(&(tpar->path_cmd), argv[*i + 3], tpar);
	if (tpar->here_doc == 1)
		fd[tpar->nb_fds][1] = open(argv[tpar->nb_fds + 3],
				O_CREAT | O_RDWR | O_APPEND, 0644);
	else
		fd[tpar->nb_fds][1] = open(argv[tpar->nb_fds + 3],
				O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (fd[tpar->nb_fds][1] == -1)
		print_error_and_free(tpar);
	child_process(fd, fd[*i][0], fd[tpar->nb_fds][1], tpar);
	clean_up(tpar);
	if (tpar->here_doc == 1)
		unlink(tpar->name_infile);
	close(fd[*i][1]);
	if (tpar->cmd_not_found == 1)
		exit(127);
}

void	case_3(int **fd, t_params *tpar, char **argv, int *i)
{
	if (tpar->path_cmd)
	{
		free(tpar->path_cmd);
		tpar->path_cmd = NULL;
	}
	tpar->cmd = return_cmd_arr(&(tpar->path_cmd), argv[*i + 3], tpar);
	child_process(fd, fd[*i][0], fd[*i + 1][1], tpar);
	clean_up(tpar);
	tpar->path_cmd = NULL;
	close(fd[*i][1]);
}

void	manage_pipes(int nb_fd, char **argv, t_params *tpar)
{
	int	**fd;
	int	i;

	i = 0;
	fd = allocate_array(nb_fd + 1);
	while (i < nb_fd)
	{
		if (pipe(fd[i]) == -1)
			exit(-1);
		i++;
	}
	i = 0;
	while (i < nb_fd)
	{
		if (i == 0)
			case_1(fd, tpar, argv, &i);
		if (i == nb_fd - 1)
			case_2(fd, tpar, argv, &i);
		if (i != nb_fd - 1)
			case_3(fd, tpar, argv, &i);
		i++;
	}
	close_all(fd);
	free_matrice_int(fd);
}

int	main(int argc, char **argv, char **env)
{
	char		*error_message;
	t_params	*tpar;

	error_message = "Error message : type at least four agruments";
	if (argc >= 5)
	{
		tpar = malloc(sizeof(t_params));
		if (ft_strcmp(argv[1], "here_doc") == 0)
			case_here_doc(tpar, argc, &argv, env);
		else
			case_normal_file(tpar, argc, argv, env);
		tpar->cmd = NULL;
		tpar->path_cmd = NULL;
		tpar->cmd_not_found = 0;
		manage_pipes(tpar->nb_fds, argv, tpar);
		free(tpar);
	}
	else
	{
		write(2, error_message, ft_strlen(error_message));
		exit(EXIT_FAILURE);
	}
	while (wait(NULL) != -1)
		;
}
