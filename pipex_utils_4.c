/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils_4.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asabir <asabir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 16:29:21 by asabir            #+#    #+#             */
/*   Updated: 2024/04/21 18:47:05 by asabir           ###   ########.fr       */
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
