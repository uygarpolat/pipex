/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_command_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: upolat <upolat@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 15:22:58 by upolat            #+#    #+#             */
/*   Updated: 2024/06/04 15:29:49 by upolat           ###   ########.fr       */
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

static void	execute_command(int argc, t_vars *t, int index)
{
	(void)argc;		// <--- Remove argc from parameters.
	(void)index;	// <--- Remove argc from parameters.


	if (access(t->full_path_with_command, F_OK) == 0)
	{
		if (access(t->full_path_with_command, X_OK) == 0)
		{
			execve(t->full_path_with_command, t->command_with_arguments, t->envp);
			error_handler3("test1", t, errno, 126);
		}
		//else if (index == argc - 2)
		error_handler3("test2", t, errno, 126);
	}
}

static void execute_command2(t_vars *t)
{
	if (access(t->command, F_OK) != 0)
	{
		if (is_file_or_dir(t->command))
			error_handler3("test3", t, errno, 127);
		else
			error_handler1("test4", t, " command not found" , 127);
		//error_handler3("test4", t, errno, 127);
	}
	if (is_file_or_dir(t->command))
	{

		if (access(t->command, X_OK) == 0)
			execve(t->command, t->command_with_arguments, t->envp);
		else
			error_handler3("test5", t, errno, 126);
	}
	error_handler3("test6", t, errno, 127); // Is this necessary?
}

int	run_command(int argc, char **argv, t_vars *t, int index)
{
	int		i;
	char	*full_path;
	i = 0;

	t->command_with_arguments = ft_split_3(argv[index]);
	t->command = t->command_with_arguments[0];
	if (!t->path_variable && access(t->command, F_OK) != 0)
		error_handler3(t->command, t, errno, 127);
	if(!t->command)
		error_handler1("test8", t, " command not found", 127);
	
	while (t->split_variable[i])
	{
		full_path = ft_strjoin(t->split_variable[i], "/");
		t->full_path_with_command = ft_strjoin(full_path, t->command);
		free(full_path);
		full_path = NULL;
		execute_command(argc, t, index);
		free(t->full_path_with_command);
		t->full_path_with_command = NULL;	
		i++;
	}
	execute_command2(t);

	ft_putstr_fd(strerror(errno), 2);
	//free_2d_array((void **)t->command_with_arguments); // The order of these last 3 lines makes no sense, the last two will never run.
	//free_2d_array((void **)t->split_variable);
	return (0);
}
