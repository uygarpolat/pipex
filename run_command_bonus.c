/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_command_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: upolat <upolat@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 15:22:58 by upolat            #+#    #+#             */
/*   Updated: 2024/05/29 21:51:12 by upolat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	run_command(char **argv, char **envp, int index)
{
	int		i;
	char	*path_variable;
	char	*full_path;
	char	*full_path_with_command;
	char	**split_variable;
	char	**command_with_arguments;
	char	*command;

	path_variable = NULL;
	while (*envp)
	{
		if (strncmp(*envp, "PATH=", 5) == 0)
		{
			path_variable = *envp + 5;
			break ;
		}
		envp++;
	}
	if (!path_variable)
	{
		ft_printf("PATH variable not found.\n");
		return (1);
	}
	split_variable = ft_split(path_variable, ':');
	command_with_arguments = ft_split_3(argv[index]);
	command = command_with_arguments[0];
	i = 0;
	while (split_variable[i])
	{
		full_path = ft_strjoin(split_variable[i], "/");
		full_path_with_command = ft_strjoin(full_path, command);
		//free(full_path_with_command);
		//full_path_with_command = NULL;
		free((void **)full_path);
		if (access(full_path_with_command, X_OK) == 0)
		{
			//ft_printf("This is the PATH that worked: %s\n", full_path_with_command); // DELETE THIS!
			execve(full_path_with_command, command_with_arguments, envp);
			perror("Failed to execute command");
		}
		free((void **)full_path_with_command);
		i++;
	}
	ft_printf("Command not found.\n");
	free_2d_array((void **)command_with_arguments);
	free_2d_array((void **) split_variable);
	return (0);
}
