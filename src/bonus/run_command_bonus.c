/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_command_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: upolat <upolat@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 15:22:58 by upolat            #+#    #+#             */
/*   Updated: 2024/06/02 22:19:44 by upolat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/pipex_bonus.h"

static void	execute_command(int argc, t_vars *t, int index)
{
	if (access(t->full_path_with_command, F_OK) == 0)
	{
		if (access(t->full_path_with_command, X_OK) == 0)
		{
			execve(t->full_path_with_command, t->command_with_arguments, t->envp);
			error_handler3("test1", t, errno, 126);
		}
		else if (index == argc - 2)
			error_handler3("test2", t, errno, 126);
	}
}

int	run_command(int argc, char **argv, t_vars *t, int index)
{
	int		i;
	char	*full_path;

	t->command_with_arguments = ft_split_3(argv[index]);
	t->command = t->command_with_arguments[0];
	if (t->command[0] == '/' || (t->command[0] == '.' && t->command[1] == '/'))
	{
		if (t->command[ft_strlen(t->command) - 1] == '/' && index == argc - 2)
			error_handler1(t->command, t, "is a directoryyy", 126);
		t->full_path_with_command = t->command;
		execute_command(argc, t, index);
	}
	i = 0;
	while (t->split_variable[i])
	{
		full_path = ft_strjoin(t->split_variable[i], "/");
		t->full_path_with_command = ft_strjoin(full_path, t->command);
		free((void **)full_path);
		execute_command(argc, t, index);
		free((void **)t->full_path_with_command);
		i++;
	}
	error_handler3(t->command, t, errno, 0);
	//free_2d_array((void **)t->command_with_arguments); // The order of these last 3 lines makes no sense, the last two will never run.
	//free_2d_array((void **)t->split_variable);
	return (0);
}
