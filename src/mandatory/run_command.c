/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_command_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: upolat <upolat@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 15:22:58 by upolat            #+#    #+#             */
/*   Updated: 2024/06/07 21:18:10 by upolat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/pipex_bonus.h"

static int	is_file_or_dir(char *str)
{
	if (!str)
		return (0);
	if (ft_strchr(str, '/') != NULL)
		return (1);
	return (0);
}

static void	execute_command(t_vars *t)
{
	if (access(t->full_path_with_command, F_OK) == 0)
	{
		if (access(t->full_path_with_command, X_OK) == 0)
		{
			execve(t->full_path_with_command,
				t->command_with_arguments, t->envp);
			error_handler3(t->command, t, errno, 126);
		}
		error_handler3(t->command, t, errno, 126);
	}
}

static void	execute_command_absolute_path(t_vars *t)
{
	if (access(t->command, F_OK) != 0)
	{
		if (is_file_or_dir(t->command))
			error_handler3(t->command, t, errno, 127);
		else
			error_handler1(t->command, t, "command not found", 127);
	}
	if (is_file_or_dir(t->command))
	{
		if (access(t->command, X_OK) == 0)
			execve(t->command, t->command_with_arguments, t->envp);
		else
			error_handler3(t->command, t, errno, 126);
	}
	error_handler3(t->command, t, errno, 127); // Either this line or the last line of run_command function is unnecessary.
}

int	run_command(char **argv, t_vars *t, int index)
{
	int		i;
	char	*full_path;

	i = 0;
	t->command_with_arguments = ft_split_2(argv[index]);
	if (t->command_with_arguments && t->command_with_arguments[0])
		t->command = t->command_with_arguments[0]; // What if argv[index] is empty and this is trying to access 0th index, which is not allowed. REMOVE THE IF CONDITION IF PROBLEMS ARISE.
	if (!t->path_variable && access(t->command, F_OK) != 0)
		error_handler3(t->command, t, errno, 127);
	if (!t->command)
		error_handler1(argv[index], t, "command not found", 127);
	while (t->split_variable && t->split_variable[i])
	{
		full_path = ft_strjoin(t->split_variable[i], "/");
		t->full_path_with_command = ft_strjoin(full_path, t->command);
		free(full_path);
		full_path = NULL;
		execute_command(t);
		free(t->full_path_with_command);
		t->full_path_with_command = NULL;
		i++;
	}
	execute_command_absolute_path(t);
	//ift_putstr_fd(strerror(errno), 2); // Either this line or the last line of execute_command2 is unnecessary.
	return (0);
}
