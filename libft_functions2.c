/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_functions2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asabir <asabir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 02:11:32 by asabir            #+#    #+#             */
/*   Updated: 2024/03/27 03:21:04 by asabir           ###   ########.fr       */
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