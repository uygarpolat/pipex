/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: upolat <upolat@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 19:20:03 by upolat            #+#    #+#             */
/*   Updated: 2024/06/11 21:41:26 by upolat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/pipex.h"

static void	initialize_t_vars(t_vars *t, char **envp)
{
	t->envp = envp;
	t->infile_fd = -42;
	t->outfile_fd = -42;
	t->pid = NULL;
	t->command = NULL;
	t->command_with_arguments = NULL;
	t->full_path_with_command = NULL;
	t->split_variable = NULL;
	t->path_variable = get_path(t->envp);
	if (t->path_variable != NULL)
	{
		t->split_variable = ft_split(t->path_variable, ':');
		if (!t->split_variable)
			error_handler2("ft_split malloc failed", t, errno, EXIT_FAILURE);
	}
}

static int	pid_wait(pid_t pid)
{
	int	status;

	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (EXIT_FAILURE);
}

static int	wait_for_children(t_vars *t)
{
	int	i;
	int	final_exit_status;

	i = 0;
	final_exit_status = 0;
	while (i < t->command_amount)
	{
		final_exit_status = pid_wait(t->pid[i][0]);
		final_exit_status = pid_wait(t->pid[i][1]);
		i++;
	}
	return (final_exit_status);
}

int	main(int argc, char **argv, char **envp)
{
	int		final_exit_status;
	t_vars	t;

	if (argc != 5)
		return (ft_putstr_fd("Argument count incorrect.\n", 2), EXIT_FAILURE);
	initialize_t_vars(&t, envp);
	t.command_amount = argc - 3;
	t.pipe_amount = t.command_amount - 1;
	fd_malloc(&t);
	create_pipes(&t);
	pids_malloc(&t);
	handle_fork(argc, argv, &t);
	close_and_free(&t);
	final_exit_status = wait_for_children(&t);
	close_free_exit(&t, final_exit_status);
	return (final_exit_status);
}
