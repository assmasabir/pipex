/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils_4.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asabir <asabir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 16:29:21 by asabir            #+#    #+#             */
/*   Updated: 2024/04/26 20:55:41 by asabir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	free_matrice_int(int **nbr)
{
	int	i;

	i = 0;
	while (nbr[i])
	{
		free(nbr[i]);
		i++;
	}
	free(nbr);
}

int	**allocate_array(int nb_fd)
{
	int	i;
	int	**fd;

	fd = malloc((nb_fd + 1) * sizeof(int *));
	i = 0;
	while (i < nb_fd)
	{
		fd[i] = malloc(2 * sizeof(int));
		i++;
	}
	fd[i] = NULL;
	return (fd);
}

void	hundle_fail_of_dup2(int **fd, t_params *tpar)
{
	free_matrice_int(fd);
	clean_up(tpar);
	free(tpar);
	perror(NULL);
	exit(EXIT_FAILURE);
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

void	print_error_and_free(t_params *tpar)
{
	clean_up(tpar);
	free(tpar);
	write(2, "permission denied:\n", 19);
	exit(EXIT_FAILURE);
}
