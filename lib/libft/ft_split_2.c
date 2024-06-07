/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: upolat <upolat@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 15:46:31 by upolat            #+#    #+#             */
/*   Updated: 2024/06/07 20:10:08 by upolat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	word_counter(char *str)
{
	int	i;
	int	wc;

	i = 0;
	wc = 0;
	while (str[i])
	{
		while (str[i] && str[i] == ' ')
			i++;
		if (str[i] && (str[i] == '\'' || str[i] == '"'))
			i = skip_quoted_section(str, i);
		wc++;
		while (str[i] && str[i] != ' ')
		{
			if (str[i] == '\'' || str[i] == '"')
				i = skip_quoted_section(str, i);
			else
				i++;
		}
	}
	return (wc);
}

static int	handle_quotes(char *str, char **arr, t_split_2 *t)
{
	int	start;
	int	end;

	start = t->i + 1;
	t->i = skip_quoted_section(str, t->i);
	end = t->i - 1;
	if (t->i > start)
	{
		arr[t->k] = malloc(sizeof(char) * (end - start + 1));
		if (arr[t->k] == NULL)
			return (0);
		ft_strncpy(arr[t->k++], &str[start], end - start);
	}
	return (1);
}

static int	handle_non_quotes(char *str, char **arr, t_split_2 *t)
{
	arr[t->k] = malloc(sizeof(char) * (t->i - t->j + 1));
	if (arr[t->k] == NULL)
		return (0);
	ft_strncpy(arr[t->k++], &str[t->j], t->i - t->j);
	return (1);
}

static int	array_creator(char *str, char **arr, t_split_2 *t)
{
	while (str[t->i])
	{
		while (str[t->i] == ' ')
			t->i++;
		t->j = t->i;
		while (str[t->i] && str[t->i] != ' ')
		{
			if (str[t->i] == '\'' || str[t->i] == '"')
			{
				if (!handle_quotes(str, arr, t))
					return (free_2d(arr), 0);
				continue ;
			}
			t->i++;
		}
		if (t->i > t->j && str[t->j] != '\'' && str[t->j] != '"')
		{
			if (!handle_non_quotes(str, arr, t))
				return (free_2d(arr), 0);
		}
	}
	arr[t->k] = NULL;
	return (1);
}

char	**ft_split_2(char *str)
{
	int			wc;
	char		**arr;
	t_split_2	t;

	t.i = 0;
	t.k = 0;
	wc = word_counter(str);
	arr = malloc(sizeof(char *) * (wc + 1));
	if (arr == NULL)
		return (NULL);
	if (array_creator(str, arr, &t) == 0)
		return (NULL);
	return (arr);
}
