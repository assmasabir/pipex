/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asabir <asabir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 23:33:49 by asabir            #+#    #+#             */
/*   Updated: 2024/04/16 23:18:17 by asabir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <sys/wait.h>
#include "get_next_line/get_next_line.h"

typedef struct Params
{
	char **cmd;
	char *path_cmd;
    int  nb_fds;
	char **env;
	char *name_infile;
	int here_doc;
} t_params;

char	**ft_split(const char *s, char c);
char	*ft_strjoin(char *str1, char *str2);
void	free_matrice(char **str);
char	**ft_cpymatrix(char ***dest, char **src);
int		ft_strlen_matrix(char **str);
int		manage_here_doc(char **argv);
int		ft_strcmp(char *s1, char *s2);
void	clean_up(t_params * tpar);
void	child_process(int (*fd)[2], int in_file, int out_file, t_params *tpar);
char	**return_cmd_arr(char **path_cmd, char *cmd, char **env);
char	*find_path(char **en);
void	close_fds(int (*fd)[2], int file_in, int file_out, int nb_fds);
int		is_cmd_found(char **path_cmd, char *str, char *cmd);
char	*ft_strdup(const char *str);