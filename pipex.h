/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asabir <asabir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 23:33:49 by asabir            #+#    #+#             */
/*   Updated: 2024/03/27 19:52:35 by asabir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <sys/wait.h>

char **ft_split(const char *s, char c);
char *ft_strchr(const char *s, int c);
char *ft_strjoin(char *str1, char *str2);
int ft_strlen(char *str);