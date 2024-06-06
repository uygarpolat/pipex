/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_with_struct.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: upolat <upolat@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 22:11:59 by upolat            #+#    #+#             */
/*   Updated: 2024/06/06 10:33:17 by upolat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

struct s_split
{
	int		flag;
	int		wc;

} t_split;

void	ft_strncpy(char *str2, char *str1, int n)
{
	int		i;

	i = 0;
	while (str1[i] && i < n)
	{
		str2[i] = str1[i];
		i++;
	}
	str2[i] = '\0';
}

int	is_delimiter(char c, t_split *t)
{
	if (t->flag == 0)
	{
		if (c == ' ')
			return (1);
		else if (c== '\'' || c == '"')
		{
			t->flag = 1;
			return (1);
		}
	}
	else
	{
		if (c== '\'' || c == '"')
		{
			if (t->flag == 1)
			{
				
			}
		}
			return (1);
		else if (c ==)
	}

	return (0);
}

char	**ft_split(char *str)
{
	int		i;
	int		j;
	int		k;
	char	**arr;

	t_split	t;
	t.flag = 0;
	t.wc = 0;
	i = 0;
	k = 0;
	while (str[i])
	{
		while (str[i] && is_delimiter(str[i], t))
			i++;
		if (str[i] && !is_delimiter(str[i], t))
			t.wc++;
		while (str[i] && !is_delimiter(str[i], t))
			i++;
	}
	arr = malloc(sizeof(char **) * (t.wc + 1));
	i = 0;

	while (str[i])
	{
		while (str[i] && is_delimiter(str[i], t))
			i++;
		j = i;
		while (str[i] && !is_delimiter(str[i], t))
			i++;
		if (i > j)
		{
			arr[k] = malloc(sizeof(char) * (i - j + 1));
			ft_strncpy(arr[k++], &str[j], i - j);
		}
	}
	arr[k] = NULL;
	return (arr);
}

#include <stdio.h>

int	main(int argc, char **argv)
{
	int	i;

	if (argc > 1)
	{
		i = 0;
		char	**str = ft_split(argv[1]);
		while (str[i])
			printf("%s\n", str[i++]);
	}
}
