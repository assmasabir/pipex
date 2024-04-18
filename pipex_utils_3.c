/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils_3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asabir <asabir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/13 15:57:41 by asabir            #+#    #+#             */
/*   Updated: 2024/04/16 00:09:54 by asabir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_putstr_fd(char *s, int fd,char **argv)
{
	int	i;

	i = 0;
	if (s && ft_strcmp(s, argv[1]))
	{
		while (s[i] != '\0')
			write(fd, &s[i++], 1);
	}
}

int manage_here_doc(char **argv)
{
	int fd;
	char *buff;
	
	buff = "just initializing";
	fd = open(argv[0],O_CREAT | O_RDWR  | O_TRUNC, 0644);
	argv[1] = ft_strjoin(argv[1], "\n");
	while(1)
	{
		buff = get_next_line(STDIN_FILENO);
		if(ft_strcmp(buff, argv[1])==0 || buff == NULL )
		{
			free(buff);
			buff = NULL;
			break;
		}
		ft_putstr_fd(buff, fd, argv);
		free(buff);
		buff = NULL;
	}
	return (fd);
}


