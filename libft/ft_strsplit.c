/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strsplit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acostaz <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/15 15:07:24 by acostaz           #+#    #+#             */
/*   Updated: 2019/02/22 13:36:42 by acostaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		free_split(char **res)
{
	int		i;

	i = -1;
	while (res[++i])
		free(res[i]);
	free(res);
}

static int	count_words(const char *s, char c)
{
	int		i;
	int		count;

	i = -1;
	count = 0;
	while (s[++i] != '\0')
		if (s[i] != c && (s[i + 1] == c || s[i + 1] == '\0'))
			count++;
	return (count);
}

static int	count_letters(const char *s, char c, int index)
{
	int		len;

	len = 0;
	while (s[index - len] != c && index - len >= 0)
		len++;
	return (len);
}

static char	**malloc_res(char **res, const char *s, char c)
{
	int		i;
	int		j;
	int		words;

	i = -1;
	j = -1;
	words = count_words(s, c);
	if (!(res = (char**)malloc(sizeof(char*) * (words + 1))))
		return (NULL);
	while (s[++i] != '\0')
	{
		words = 0;
		if (s[i] != c && (s[i + 1] == c || s[i + 1] == '\0'))
		{
			words = count_letters(s, c, i);
			if (!(res[++j] = ft_strnew(words + 1)))
			{
				free_split(res);
				return (NULL);
			}
		}
	}
	return (res);
}

char		**ft_strsplit(char const *s, char c)
{
	int		words;
	int		i;
	int		j;
	int		k;
	char	**res;

	i = -1;
	k = -1;
	res = NULL;
	if (!(s != NULL && (res = malloc_res(res, s, c))))
		return (NULL);
	words = count_words(s, c);
	while (s[++i] != '\0')
	{
		if (s[i] != c && (s[i + 1] == c || s[i + 1] == '\0'))
		{
			j = -1;
			words = count_letters(s, c, i);
			res[++k][words] = '\0';
			while (++j < words)
				res[k][j] = s[i - words + j + 1];
		}
	}
	res[++k] = 0;
	return (res);
}
