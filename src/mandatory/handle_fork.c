/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_fork.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: upolat <upolat@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 11:28:22 by upolat            #+#    #+#             */
/*   Updated: 2024/06/11 21:11:26 by upolat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/pipex.h"

static void	fork_fail(t_vars *t, int i, int flag)
{
	int	limit;

	limit = 0;
	while (limit < i)
	{
		waitpid(t->pid[limit][0], NULL, 0);
		waitpid(t->pid[limit][1], NULL, 0);
		limit++;
	}
	if (flag)
		waitpid(t->pid[limit][0], NULL, 0);
	error_handler2("Fork fail", t, errno, EXIT_FAILURE);
}

static void	first_child_fork(char **argv, t_vars *t, int i)
{
	t->pid[i][0] = fork();
	if (t->pid[i][0] == -1)
		fork_fail(t, i, 0);
	if (t->pid[i][0] == 0)
	{
		if (i == 0)
		{
			open_infile(argv, t);
			if (dup2(t->infile_fd, STDIN_FILENO) == -1)
				error_handler2("Dup2 fail", t, errno, EXIT_FAILURE);
		}
		else if (dup2(t->fd[i - 1][0], STDIN_FILENO) == -1)
			error_handler2("Dup2 fail", t, errno, EXIT_FAILURE);
		if (dup2(t->fd[i][1], STDOUT_FILENO) == -1)
			error_handler2("Dup2 fail", t, errno, EXIT_FAILURE);
		close_and_free(t);
		run_command(argv, t, i + 2);
	}
}

static void	second_child_fork(int argc, char **argv, t_vars *t, int i)
{
	t->pid[i][1] = fork();
	if (t->pid[i][1] == -1)
		fork_fail(t, i, 1);
	if (t->pid[i][1] == 0)
	{
		if (dup2(t->fd[i - 1][0], STDIN_FILENO) == -1)
			error_handler2("Dup2 fail", t, errno, EXIT_FAILURE);
		if (i == t->pipe_amount)
		{
			open_outfile(argc, argv, t);
			if (dup2(t->outfile_fd, STDOUT_FILENO) == -1)
				error_handler2("Dup2 fail", t, errno, EXIT_FAILURE);
		}
		else if (dup2(t->fd[i][1], STDOUT_FILENO) == -1)
			error_handler2("Dup2 fail", t, errno, EXIT_FAILURE);
		close_and_free(t);
		run_command(argv, t, i + 2);
	}
}

void	handle_fork(int argc, char **argv, t_vars *t)
{
	int	i;

	i = 0;
	while (i < t->command_amount)
	{
		if (i == 0)
			first_child_fork(argv, t, i);
		else
			second_child_fork(argc, argv, t, i);
		i++;
	}
}
