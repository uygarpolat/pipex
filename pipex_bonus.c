/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: upolat <upolat@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 19:20:03 by upolat            #+#    #+#             */
/*   Updated: 2024/05/31 12:57:48 by upolat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	main(int argc, char **argv, char **envp)
{
	int		**fd;
	int		infile_fd;
	int		outfile_fd;
	pid_t	**pid;
	int		i;
	int		heredoc_exists;
	
	if (argc < 5)
	{
		return (write(2, "Argument error!\n", 17), EXIT_FAILURE);
	}
	heredoc_exists = 0;
	if (ft_strncmp(argv[1], "here_doc", 9) == 0)
	{
		heredoc_exists = 1;
		infile_fd = handle_here_doc(argc, argv[2]);
	}
	else
		infile_fd = open(argv[1], O_RDONLY);
	if (infile_fd < 0)
		error_handler3(argv[1 + heredoc_exists], errno, 0);
	outfile_fd = open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (outfile_fd < 0)
		error_handler3(argv[argc - 1], errno, 0);
	
	fd = fd_malloc(argc, heredoc_exists);
	i = 0;
	while (i < argc - 4 - heredoc_exists)
	{
		if (pipe(fd[i]) == -1)
		{
			printf("Error with creating pipe\n");
			close_and_free(fd, infile_fd, outfile_fd, argc, heredoc_exists);
			return (1);
		}
		i++;
	}
	pid = malloc((argc - 3 - heredoc_exists) * sizeof(pid_t));
	if (!pid)
	{
    	perror("Failed to allocate memory for pids");
    	return (EXIT_FAILURE);
	}
	i = 0;
	while (i < argc - 4 - heredoc_exists)
	{
		pid[i][0] = fork();
		if (pid[i][0] == 0)
		{
			if (i == 0)
				dup2(infile_fd, STDIN_FILENO);
			else
				dup2(fd[i - 1][0], STDIN_FILENO);
			dup2(fd[i][1], STDOUT_FILENO);
			close_and_free(fd, infile_fd, outfile_fd, argc, heredoc_exists);
			run_command(argv, envp, i + 2 + heredoc_exists);
		}
		pid[i][1] = fork();
		if (pid[i][1] == 0)
		{
			dup2(fd[i][0], STDIN_FILENO);
			if (i == argc - 5 - heredoc_exists)
				dup2(outfile_fd, STDOUT_FILENO);
			else
				dup2(fd[i + 1][1], STDOUT_FILENO);
			close_and_free(fd, infile_fd, outfile_fd, argc, heredoc_exists);
			run_command(argv, envp, i + 3 + heredoc_exists);
		}
		i++;
	}
	close_and_free(fd, infile_fd, outfile_fd, argc, heredoc_exists);
	i = 0;
	while (i < argc - 4 - heredoc_exists)
	{
		waitpid(pid[i][0], NULL, 0);
		waitpid(pid[i][1], NULL, 0);
		i++;
	}
	free_2d_array((void **) pid);
	return (0);
}
