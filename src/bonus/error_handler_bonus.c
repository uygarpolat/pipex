/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handler_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: upolat <upolat@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 14:23:58 by upolat            #+#    #+#             */
/*   Updated: 2024/06/05 19:17:33 by upolat           ###   ########.fr       */
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

	i = 0;
	if (t->infile_fd >= 0)
		close(t->infile_fd);
	if (t->outfile_fd >= 0)
		close(t->outfile_fd);
	while (i < t->pipe_amount)
	{
		close(t->fd[i][0]);
		close(t->fd[i][1]);
		i++;
	}
	//if (t->fd)
	//	free_2d_array((void **)t->fd); // This is commented out because it is already freed at the very end of main.
	//if (t->split_variable)
	//	free_2d_array((void **)t->split_variable); // This was moved to close_free_exit, because first and second_child_fork functions are calling close_and_free early in the code, which is too soon to free split variable.
}

void	close_free_exit(t_vars *t, int exitcode)
{
	close_and_free(t);
	if (t->here_doc_fd >= 0)
		close(t->here_doc_fd);
	if (t->pid)
		free_2d_array((void **)t->pid);
	if (t->split_variable)
		free_2d_array((void **)t->split_variable); // This is being double-freed currently. Hence the error on pipex tester from tests 18 onwards.
	//if (t->full_path_with_command)
	//	free(t->full_path_with_command); // When I uncomment this, getting double freeing errors from pipex tester.
	if (t->command_with_arguments)
		free_2d_array((void **)t->command_with_arguments);
	if (access(".here_doc", F_OK) == 0)
		unlink(".here_doc");
	exit(exitcode);
}
