/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: upolat <upolat@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 19:20:03 by upolat            #+#    #+#             */
/*   Updated: 2024/06/02 01:43:42 by upolat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/pipex_bonus.h"

void test_function2(int argc, char **argv, t_vars *t);
int	pid_wait(pid_t pid);

void	initialize_t_vars(t_vars *t, char **argv, char **envp)
{
	t->envp = envp;
	t->infile_fd = -2;
	t->outfile_fd = -2;
	//t->pipes = NULL;
	t->pid = NULL;
	t->command = NULL;
	t->command_with_arguments = NULL;
	t->full_path_with_command = NULL;
	if (!ft_strncmp(argv[1], "here_doc", 9))
		t->here_doc = 1;
	else
		t->here_doc = 0;
	t->path_variable = get_path2(envp); // What happens if get_path2 returns NULL
	if (t->path_variable != NULL)
	{
		t->split_variable = ft_split(t->path_variable, ':');
		//if (!t->split_variable)
			//error_exit("ft_split malloc failed\n", t, 1); // -------------> Definitely comment this back in after creating a proper error checking function.
	}
	//else
		// Do I need an else condition?
}

int	main(int argc, char **argv, char **envp)
{
	int		i;

	t_vars	t;
	if (argc == 1
		|| (ft_strncmp(argv[1], "here_doc", 9) == 0 && argc < 6) || argc < 5)
		return (write(2, "Argument error!\n", 17), EXIT_FAILURE);
	initialize_t_vars(&t, argv, envp);
	t.command_amount = argc - 3 - t.here_doc;
	t.pipe_amount = t.command_amount - 1;
	fd_malloc(&t);
	i = 0;
	while (i < t.pipe_amount)
	{
		if (pipe(t.fd[i]) == -1)
		{
			close_and_free(&t);
			error_handler3(argv[argc - 1], &t, errno, 0);
		}
		i++;
	}
	pids_malloc(&t);	
	if (!t.pid)
	{
    	perror("Failed to allocate memory for pids");
    	return (EXIT_FAILURE);
	}
	handle_fork(argc, argv, &t);
	close_and_free(&t);
	i = 0;
	while (i < t.pipe_amount)
	{
		pid_wait(t.pid[i][0]);
		pid_wait(t.pid[i][1]);
		i++;
	}
	free_2d_array((void **) t.pid);
	return (0);
}

int	pid_wait(pid_t pid)
{
	int	status;

	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return(EXIT_FAILURE);
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
		run_command(argv, t, i + 2 + t->here_doc);
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
		run_command(argv, t, i + 3 + t->here_doc);
	}
}

void handle_fork(int argc, char **argv, t_vars *t)
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
