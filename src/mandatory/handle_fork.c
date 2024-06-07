/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_fork_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: upolat <upolat@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 11:28:22 by upolat            #+#    #+#             */
/*   Updated: 2024/06/07 15:44:29 by upolat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/pipex_bonus.h"

static void	fork_fail(t_vars *t, int i, int flag)
{
	int limit;

	limit = 0;
	while (limit < i)
	{
		waitpid(t->pid[limit][0], NULL, 0);
		waitpid(t->pid[limit][1], NULL, 0);
		limit++;
	}
	if (flag)
		waitpid(t->pid[limit][0], NULL, 0);
	error_handler3("Fork fail", t, errno, EXIT_FAILURE);
}

static void	first_child_fork(int argc, char **argv, t_vars *t, int i)
{
	t->pid[i][0] = fork();
	if (t->pid[i][0] == -1)
		fork_fail(t, i, 0);
	if (t->pid[i][0] == 0)
	{
		if (i == 0)
		{
			open_infile(argc, argv, t);
			dup2(t->infile_fd, STDIN_FILENO);
		}
		else
			dup2(t->fd[i - 1][0], STDIN_FILENO);
		dup2(t->fd[i][1], STDOUT_FILENO);
		close_and_free(t);
		run_command(argv, t, i + 2 + t->here_doc);
	}
}

static void	second_child_fork(int argc, char **argv, t_vars *t, int i)
{
	t->pid[i][1] = fork();
	if (t->pid[i][1] == -1)
		fork_fail(t, i, 1);
	if (t->pid[i][1] == 0)
	{
		dup2(t->fd[i][0], STDIN_FILENO);
		if (i == t->pipe_amount - 1)
		{
			open_outfile(argc, argv, t);
			dup2(t->outfile_fd, STDOUT_FILENO);
		}
		else
			dup2(t->fd[i + 1][1], STDOUT_FILENO);
		close_and_free(t);
		run_command(argv, t, i + 3 + t->here_doc);
	}
}

void	handle_fork(int argc, char **argv, t_vars *t)
{
	int	i;

	i = 0;
	while (i < t->pipe_amount)
	{
		first_child_fork(argc, argv, t, i);
		second_child_fork(argc, argv, t, i);
		i++;
	}
}
