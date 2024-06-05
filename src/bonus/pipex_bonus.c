/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: upolat <upolat@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 19:20:03 by upolat            #+#    #+#             */
/*   Updated: 2024/06/05 11:35:54 by upolat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/pipex_bonus.h"

int		pid_wait(pid_t pid);
void	create_pipes(t_vars *t);
int		wait_for_children(t_vars *t);

void	initialize_t_vars(t_vars *t, char **argv, char **envp)
{
	t->envp = envp;
	t->infile_fd = -2;
	t->outfile_fd = -2;
	t->pid = NULL;
	t->command = NULL;
	t->command_with_arguments = NULL;
	t->full_path_with_command = NULL;
	if (!ft_strncmp(argv[1], "here_doc", 9))
		t->here_doc = 1;
	else
		t->here_doc = 0;
	t->path_variable = get_path2(envp); // Whatif get_path2 returns NULL
	if (t->path_variable != NULL)
	{
		t->split_variable = ft_split(t->path_variable, ':');
		if (!t->split_variable)
			exit(EXIT_FAILURE);
			//error_handler1("ft_split: ", t, "malloc failed.", EXIT_FAILURE);
	}
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
	if (!t.pid)
	{
		perror("Failed to allocate memory for pids");
		return (EXIT_FAILURE);
	}
	handle_fork(argc, argv, &t);
	close_and_free(&t);
	final_exit_status = wait_for_children(&t);
	free_2d_array((void **) t.pid); // Is this necessary? How about unlinking the here_doc?
	return (final_exit_status);
}

int	pid_wait(pid_t pid)
{
	int	status;

	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (EXIT_FAILURE);
}

void	create_pipes(t_vars *t)
{
	int	i;

	i = 0;
	while (i < t->pipe_amount)
	{
		if (pipe(t->fd[i]) == -1)
		{
			close_and_free(t);
			error_handler3("Enter a proper error handling function here!!!!!!!!!!!", t, errno, EXIT_FAILURE); // -----> Is EXIT_FAILURE correct here?
		}
		i++;
	}
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
