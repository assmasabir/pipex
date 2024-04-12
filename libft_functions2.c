/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_functions2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asabir <asabir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 02:11:32 by asabir            #+#    #+#             */
/*   Updated: 2024/04/12 15:15:29 by asabir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char *allocate(char const *s1, char const *s2)
{
	int len;
	char *res;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	len = ft_strlen((char *)s1) + ft_strlen((char *)s2);
	res = (char *)malloc((len + 1) * sizeof(char));
	return (res);
}

char *ft_strjoin(char *s1, char *s2)
{
	char *res;
	int i;
	int j;

	i = 0;
	j = 0;
	res = allocate(s1, s2);
	if (!res)
		return (NULL);
	while (s1[j] != '\0')
	{
		res[i] = s1[j];
		i++;
		j++;
	}
	j = 0;
	while (s2[j] != '\0')
	{
		res[i] = s2[j];
		i++;
		j++;
	}
	res[i] = '\0';
	return (res);
}

char *ft_strcpy(char **dest, char *src)
{
	int i;

	i = 0;
	*dest = malloc(ft_strlen(src)+1);
	while(src[i] != '\0')
	{
		(*dest)[i]=src[i];
		i++;
	}
	(*dest)[i] = '\0';
	return(*dest);
}
int ft_strlen_matrix(char **str)
{
	int i;

	i = 0;
	while(str[i])
	{
		i++;
	}
	return(i);
}
char **ft_cpymatrix(char ***dest, char **src) 
{
    int i = 0;
    *dest = malloc((ft_strlen_matrix(src) + 1) * sizeof(char *));
    if (*dest == NULL) {
        exit(EXIT_FAILURE);
    }
    while (src[i]) {
        int j = 0;
        (*dest)[i] = (char *)malloc(strlen(src[i]) + 1); 
        if ((*dest)[i] == NULL) {
            exit(EXIT_FAILURE);
        }
        while (src[i][j] != '\0') {
            (*dest)[i][j] = src[i][j];
            // printf("-----> %c %c\n", (*dest)[i][j] , src[i][j]);
            j++;
        }
        (*dest)[i][j] = '\0';
        i++;
    }
    (*dest)[i] = NULL;
    return *dest;
}
