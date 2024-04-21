/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils_3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asabir <asabir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/13 15:57:41 by asabir            #+#    #+#             */
/*   Updated: 2024/04/21 18:48:57 by asabir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_putstr_fd(char *s, int fd, char **argv)
{
	int	i;

	i = 0;
	if (s && ft_strcmp(s, argv[1]))
	{
		while (s[i] != '\0')
			write(fd, &s[i++], 1);
	}
}

int	manage_here_doc(char **argv)
{
	int		fd;
	char	*buff;

	buff = "just initializing";
	fd = open(argv[0], O_CREAT | O_RDWR | O_TRUNC, 0644);
	argv[1] = ft_strjoin(argv[1], "\n");
	while (1)
	{
		buff = get_next_line(STDIN_FILENO);
		if (ft_strcmp(buff, argv[1]) == 0 || buff == NULL)
		{
			free(buff);
			buff = NULL;
			break ;
		}
		ft_putstr_fd(buff, fd, argv);
		free(buff);
		buff = NULL;
	}
	return (fd);
}

void	close_all(int **fd, int nb_fd)
{
	int	i;

	i = 0;
	while (i < nb_fd)
	{
		if (fd[i][0])
			close(fd[i][0]);
	}
}

void	case_here_doc(t_params *tpar, int argc)
{
	tpar->nb_fds = argc - 5;
	tpar->name_infile = "here_doc";
	tpar->here_doc = 1;
}

void	case_normal_file(t_params *tpar, int argc, char **argv)
{
	tpar->nb_fds = argc - 4;
	tpar->name_infile = argv[1];
	tpar->here_doc = 0;
}
