/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_command_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: upolat <upolat@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 15:22:58 by upolat            #+#    #+#             */
/*   Updated: 2024/06/01 20:06:15 by upolat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/pipex_bonus.h"

static void	execute_command(t_vars *t)
{
	if (access(t->full_path_with_command, F_OK) == 0)
	{
		if (access(t->full_path_with_command, X_OK) == 0)
			execve(t->full_path_with_command, t->command_with_arguments, t->envp);
		error_handler3(t->full_path_with_command, errno, 126); 
	}
}

int	run_command(char **argv, t_vars *t, int index)
{
	int		i;
	char	*full_path;

	t->command_with_arguments = ft_split_3(argv[index]);
	t->command = t->command_with_arguments[0];
	if (t->command[0] == '/' || (t->command[0] == '.' && t->command[1] == '/'))
	{
		t->full_path_with_command = t->command;
		execute_command(t);
	}
	i = 0;
	while (t->split_variable[i])
	{
		full_path = ft_strjoin(t->split_variable[i], "/");
		t->full_path_with_command = ft_strjoin(full_path, t->command);
		free((void **)full_path);
		execute_command(t);
		free((void **)t->full_path_with_command);
		i++;
	}
	error_handler3(t->command, errno, 0);
	free_2d_array((void **)t->command_with_arguments);
	free_2d_array((void **)t->split_variable);
	return (0);
}
