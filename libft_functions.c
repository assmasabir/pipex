/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_functions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asabir <asabir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 23:31:44 by asabir            #+#    #+#             */
/*   Updated: 2024/04/16 18:18:02 by asabir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int number_of_strings(const char *str, char c)
{
	int i;
	int len;

	i = 0;
	len = 0;
	if (!str)
		return (0);
	while (str[i] != '\0')
	{
		while (str[i] == c)
			i++;
		if (str[i] && str[i] != c)
			len++;
		while (str[i] && str[i] != c)
			i++;
	}
	return (len);
}

char *ft_strndup(const char *str, int n)
{
	int j;
	char *dest;

	j = 0;
	if (str == NULL)
		return (NULL);
	dest = (char *)malloc(sizeof(char) * (n + 1));
	if (!dest)
		return (NULL);
	while (str[j] != '\0' && j < n)
	{
		dest[j] = str[j];
		j++;
	}
	dest[j] = '\0';
	return (dest);
}

static char **freetab(char **tab)
{
	int i;

	i = 0;
	while (tab[i] != NULL)
	{
		free(tab[i]);
		i++;
	}
	free(tab);
	return (NULL);
}

char **make(const char *s, char **res, char c)
{
	int i;
	int j;
	int len;

	i = 0;
	j = 0;
	while (s[j] != '\0')
	{
		while (s[j] == c)
			j++;
		if (s[j])
		{
			len = 0;
			while (s[j + len] && s[j + len] != c)
				len++;
			res[i] = ft_strndup(s + j, len);
			if (!res[i])
				return (freetab(res));
			i++;
			j += len;
		}
	}
	res[i] = NULL;
	return (res);
}

char **ft_split(const char *s, char c)
{
	char **res;
	int n;

	if (s == NULL)
	{
		return (NULL);
	}
	n = number_of_strings(s, c);
	res = (char **)malloc((n + 1) * sizeof(char *));
	if (!res)
		return (NULL);
	res = make(s, res, c);
	if (!res)
		return (NULL);
	return (res);
}
