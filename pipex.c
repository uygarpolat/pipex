/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: upolat <upolat@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 22:28:18 by upolat            #+#    #+#             */
/*   Updated: 2024/05/10 10:04:02 by upolat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include "ft_printf.h"
#include "libft.h"

void	free_2d(char **arr)
{
	int i;

	i = 0;
	while (arr[i])
		free(arr[i++]);
	free(arr);
}

int	main(int argc, char **argv, char **envp)
{
	char	*path_variable;
	int		i;
	char	**split_variable;
	char	*command;
	char	*full_path;
	char	*full_path_no_slash;

	i = 0;
	command = argv[2];
	if (argc != 5)
	{
		ft_printf("Not enough parameters.");
		return (1);
	}
	path_variable = NULL;
	split_variable = NULL;
	while (*envp)
	{
		if (strncmp(envp[i], "PATH=", 5) == 0)
		{
			path_variable = *envp + 5;
			split_variable = ft_split(path_variable, ':');
			break ;
		}
		envp++;
	}
	i = 0;
	while (split_variable[i])
	{
		//if (split_variable[i][ft_strlen(split_variable[i]) - 1] != '/')
		full_path_no_slash = ft_strjoin(split_variable[i], "/");
		full_path = ft_strjoin(full_path_no_slash, command);
		free(full_path_no_slash);
		if (access(full_path, X_OK) == 0)
		{
			ft_printf("Found: %s\n", full_path);
			free(full_path);
			free_2d(split_variable);
			break ;
		}
		free(full_path);
		i++;
	}
	return (0);
}
