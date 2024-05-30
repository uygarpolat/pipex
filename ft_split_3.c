/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: upolat <upolat@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 15:46:31 by upolat            #+#    #+#             */
/*   Updated: 2024/05/29 20:39:45 by upolat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "pipex_bonus.h"

int	is_delimiter(char c)
{
	if (c == ' ' || c == '\t' || c == '\n')
		return (1);
	return (0);
}

static int skip_quoted_section(char *str, int i)
{
	char quote_char = str[i];
	i++;
	while (str[i] && str[i] != quote_char)
		i++;
	if (str[i] == quote_char)
		i++;

	return (i);
}

static void	free_2d(char **str)
{
	int	i;

	i = 0;
	while (str[i])
		free(str[i++]);
	free(str);
}

static void	ft_strncpy(char *s1, char *s2, int n)
{
	int	i;

	i = 0;
	while (s2[i] && i < n)
	{
		s1[i] = s2[i];
		i++;
	}
	s1[i] = '\0';
}

static int	word_counter(char *str)
{
	int	i;
	int	wc;

	i = 0;
	wc = 0;
	while (str[i])
	{
		while (str[i] && (str[i] == ' ' || str[i] == '\t' || str[i] == '\n'))
			i++;
		if (str[i] && (str[i] == '\'' || str[i] == '"'))
			i = skip_quoted_section(str, i);
		wc++;
		while (str[i] && !is_delimiter(str[i]))
		{
			if (str[i] == '\'' || str[i] == '"')
				i = skip_quoted_section(str, i);
			else
				i++;
		}
    }
    return wc;
}
/*
int	array_creator(char *str, char **arr, int i, int k)
{
	int		j;

	while (str[i])
	{
		while (str[i] && (str[i] == ' ' || str[i] == '\t' || str[i] == '\n'))
			i++;
		j = i;
		while (str[i] && !(str[i] == ' ' || str[i] == '\t' || str[i] == '\n'))
       {
            if (str[i] == '\'' || str[i] == '"')
                i = skip_quoted_section(str, i);
            else
                i++;
        }
		if (i > j)
		{
			arr[k] = malloc(sizeof(char *) * (i - j + 1));
			if (arr[k] == NULL)
			{
				free_2d(arr);
				return (0);
			}
			ft_strncpy(arr[k++], &str[j], i - j);
		}
	}
	arr[k] = NULL;
	return (1);
}
*/

int array_creator(char *str, char **arr, int i, int k)
{
    int j;

    while (str[i])
    {
        while (str[i] && is_delimiter(str[i]))
            i++;
        j = i;
        while (str[i] && !is_delimiter(str[i]))
        {
            if (str[i] == '\'' || str[i] == '"')
            {
                int start = i + 1;  // Start just after the opening quote
                i = skip_quoted_section(str, i);
                int end = i - 1;  // End just before the closing quote
                if (i > start)
                {
                    arr[k] = malloc(sizeof(char) * (end - start + 1));
                    if (arr[k] == NULL)
                    {
                        free_2d(arr);
                        return (0);
                    }
                    ft_strncpy(arr[k++], &str[start], end - start);
                    continue;  // Move to the next character after the quote
                }
            }
            else
                i++;
        }
        if (i > j && (str[j] != '\'' && str[j] != '"'))  // Ensure not to start with a quote
        {
            arr[k] = malloc(sizeof(char) * (i - j + 1));
            if (arr[k] == NULL)
            {
                free_2d(arr);
                return (0);
            }
            ft_strncpy(arr[k++], &str[j], i - j);
        }
    }
    arr[k] = NULL;
    return (1);
}

char	**ft_split_3(char *str)
{
	int		wc;
	char	**arr;

	wc = word_counter(str);
	arr = malloc(sizeof(char **) * (wc + 1));
	if (arr == NULL)
		return (NULL);
	if (array_creator(str, arr, 0, 0) == 0)
		return (NULL);
	return (arr);
}
/*
#include <stdio.h>

int	main(int argc, char **argv)
{
	char	**arr;
	int		i;

	if (argc == 2)
	{
		i = 0;
		arr = ft_split(argv[1]);
		if (arr == NULL)
			return (0);
		while (arr[i])
		{
			printf("%s\n", arr[i]);
			i++;
		}
		free_2d(arr);
	}
}
*/
