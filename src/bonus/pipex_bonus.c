/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: upolat <upolat@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 19:20:03 by upolat            #+#    #+#             */
/*   Updated: 2024/06/07 01:37:47 by upolat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/pipex_bonus.h"

void	initialize_t_vars(t_vars *t, char **argv, char **envp)
{
	t->envp = envp;
	t->infile_fd = -1;
	t->outfile_fd = -1;
	t->here_doc_fd = -1;
	t->pid = NULL;
	t->command = NULL;
	t->command_with_arguments = NULL;
	t->full_path_with_command = NULL;
	t->split_variable = NULL;
	if (!ft_strncmp(argv[1], "here_doc", 9))
		t->here_doc = 1;
	else
		t->here_doc = 0;
	t->path_variable = get_path2(envp); // Whatif get_path2 returns NULL
	if (t->path_variable != NULL)
	{
		t->split_variable = ft_split(t->path_variable, ':');
		if (!t->split_variable)
			error_handler3("ft_split malloc failed", t, errno, EXIT_FAILURE);
	}
}

int	pid_wait(pid_t pid)
{
	int	status;

	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (EXIT_FAILURE);
}

int	wait_for_children(t_vars *t)
{
	int	i;
	int	final_exit_status;

	i = 0;
	final_exit_status = 0;
	while (i < t->pipe_amount)
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

	if (argc == 1
		|| (ft_strncmp(argv[1], "here_doc", 9) == 0 && argc < 6) || argc < 5)
		return (write(2, "Argument error!\n", 17), EXIT_FAILURE); //Consider changing it to ft_putstr_fd.
	initialize_t_vars(&t, argv, envp);
	t.command_amount = argc - 3 - t.here_doc;
	t.pipe_amount = t.command_amount - 1;
	fd_malloc(&t);
	create_pipes(&t);
	pids_malloc(&t);
	handle_fork(argc, argv, &t);
	close_and_free(&t);
	final_exit_status = wait_for_children(&t);
	free_2d_array((void ***) &t.pid);
	free_2d_array((void ***) &t.fd);
	if (t.split_variable)
		free_2d_array((void ***)&t.split_variable);
	if (t.here_doc_fd >= 0)
		close(t.here_doc_fd);
	return (final_exit_status);
}
