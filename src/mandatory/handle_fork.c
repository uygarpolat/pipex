/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_fork_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: upolat <upolat@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 11:28:22 by upolat            #+#    #+#             */
/*   Updated: 2024/06/05 11:30:00 by upolat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/pipex_bonus.h"

void	first_child_fork(int argc, char **argv, t_vars *t, int i)
{
	t->pid[i][0] = fork();
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

void	second_child_fork(int argc, char **argv, t_vars *t, int i)
{
	t->pid[i][1] = fork();
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
