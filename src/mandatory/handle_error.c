/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: upolat <upolat@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 14:23:58 by upolat            #+#    #+#             */
/*   Updated: 2024/06/08 12:49:20 by upolat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/pipex.h"

void	error_handler1(char *str, t_vars *t, char *str2, int errorcode)
{
	ft_putstr_fd("pipex: ", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(str2, 2);
	ft_putstr_fd("\n", 2);
	close_free_exit(t, errorcode);
}

void	error_handler2(char *str, t_vars *t, int errnum, int errorcode)
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
		close(t->infile_fd);
	t->infile_fd = -42;
	if (t->outfile_fd >= 0)
		close(t->outfile_fd);
	t->outfile_fd = -42;
	i = 0;
	while (i < t->pipe_amount)
	{
		if (t->fd[i][0] != -42)
		{
			close(t->fd[i][0]);
			t->fd[i][0] = -42;
		}
		if (t->fd[i][1] != -42)
		{
			close(t->fd[i][1]);
			t->fd[i][1] = -42;
		}
		i++;
	}
}

void	close_free_exit(t_vars *t, int exitcode)
{
	close_and_free(t);
	if (t->split_variable)
		free_2d_array((void ***)&t->split_variable);
	if (t->full_path_with_command)
	{
		free(t->full_path_with_command);
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
