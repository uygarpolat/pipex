/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: upolat <upolat@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 19:20:03 by upolat            #+#    #+#             */
/*   Updated: 2024/06/04 21:36:10 by upolat           ###   ########.fr       */
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
		run_command(argc, argv, t, i + 2 + t->here_doc);
	}
}

void	second_child_fork(int argc, char **argv, t_vars *t, int i)
{
	t->pid[i][1] = fork();
	if (t->pid[i][1] == 0)
	{
		dup2(t->fd[i][0], STDIN_FILENO);
		if (i == t->pipe_amount - 1) // was (i == argc - 5 - heredoc_exists), focus here if errors are happening
		{
			open_outfile(argc, argv, t);
			dup2(t->outfile_fd, STDOUT_FILENO);
		}
		else
			dup2(t->fd[i + 1][1], STDOUT_FILENO);
		close_and_free(t);
		run_command(argc, argv, t, i + 3 + t->here_doc);
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
