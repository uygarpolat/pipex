/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handler_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: upolat <upolat@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 14:23:58 by upolat            #+#    #+#             */
/*   Updated: 2024/06/06 00:36:54 by upolat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/pipex_bonus.h"

void	error_handler1(char *str, t_vars *t, char *str2, int errorcode)
{
	ft_putstr_fd("pipex: ", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(str2, 2);
	ft_putstr_fd("\n", 2);
	close_free_exit(t, errorcode);
}

void	error_handler3(char *str, t_vars *t, int errnum, int errorcode)
{
	ft_putstr_fd("pipex: ", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(strerror(errnum), 2);
	ft_putstr_fd("\n", 2);
	close_free_exit(t, errorcode);
}

void	close_and_free(t_vars *t)
{
	int	i;
	if (t->infile_fd >= 0)
	{
		close(t->infile_fd);
		t->infile_fd = -1;
	}
	if (t->outfile_fd >= 0)
	{
		close(t->outfile_fd);
		t->outfile_fd = -1;
	}
	i = -1;
	while (++i < t->pipe_amount)
	{
		if (t->fd[i][0] != -1)
		{
			close(t->fd[i][0]);
			t->fd[i][0] = -1;
		}
		if (t->fd[i][1] != -1)
		{
			close(t->fd[i][1]);
			t->fd[i][1] = -1;
		}
	}
}

void	close_free_exit(t_vars *t, int exitcode)
{
	close_and_free(t);
	if (t->here_doc_fd >= 0)
	{
		close(t->here_doc_fd);
		t->here_doc_fd = -1;
	}
	if (t->split_variable)
		free_2d_array((void ***)&t->split_variable);
	if (t->full_path_with_command)
	{
		free(t->full_path_with_command); // When I uncomment this, I used to get double freeing errors from pipex tester.
		t->full_path_with_command = NULL;
	}
	if (t->command_with_arguments)
		free_2d_array((void ***)&t->command_with_arguments);
	if (t->pid)
		free_2d_array((void ***)&t->pid);
	if (t->fd)
		free_2d_array((void ***)&t->fd);
	if (access(".here_doc", F_OK) == 0)
		unlink(".here_doc");
	exit(exitcode);
}
