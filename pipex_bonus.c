/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: upolat <upolat@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 19:20:03 by upolat            #+#    #+#             */
/*   Updated: 2024/05/23 08:50:29 by upolat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include "ft_printf.h"
#include "libft.h"

int		run_command(char **argv, char **envp, int index);
int		handle_here_doc(char *argv2);

void	free_2d_array(void **arr)
{
	int	i;

	i = 0;
	if (!arr)
		return ;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

int	**fd_malloc(int argc, int heredoc_exists)
{
	int	i;
	int	**fd;

	i = 0;
	fd = malloc(sizeof(int *) * (argc - 4 - heredoc_exists + 1));
	if (fd == NULL)
		return (0);
	while (i < argc - 4 - heredoc_exists)
	{
		fd[i] = malloc(sizeof(int) * 2);
		if (fd[i] == NULL)
		{
			free_2d_array((void **)fd);
			return (0);
		}
		i++;
	}
	fd[i] = 0;
	return (fd);
}

void	close_and_free(int **fd, int infile_fd, int outfile_fd, int argc, int heredoc_exists)
{
	int	i;

	i = 0;
	close(infile_fd);
	close(outfile_fd);
	while (i < argc - 4 - heredoc_exists)
	{
		close(fd[i][0]);
		close(fd[i][1]);
		i++;
	}
	free_2d_array((void **)fd);
}

int	main(int argc, char **argv, char **envp)
{
	int		**fd;
	int		infile_fd;
	int		outfile_fd;
	pid_t	pid1;
	pid_t	pid2;
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
		infile_fd = handle_here_doc(argv[2]);
	}
	else
		infile_fd = open(argv[1], O_RDONLY);
	if (infile_fd < 0)
	{
		perror("Failed to open input file");
		return (1);
	}
	outfile_fd = open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (outfile_fd < 0)
	{
		perror("Failed to open output file");
		close(infile_fd);
		return (1);
	}
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
	i = 0;
	while (i < argc - 4 - heredoc_exists)
	{
		pid1 = fork();
		if (pid1 == 0)
		{
			if (i == 0)
				dup2(infile_fd, STDIN_FILENO);
			else
				dup2(fd[i - 1][0], STDIN_FILENO);
			dup2(fd[i][1], STDOUT_FILENO);
			close_and_free(fd, infile_fd, outfile_fd, argc, heredoc_exists);
			run_command(argv, envp, i + 2 + heredoc_exists);
		}
		pid2 = fork();
		if (pid2 == 0)
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
		waitpid(pid1, NULL, 0);
		waitpid(pid2, NULL, 0);
		i++;
	}
	return (0);
}

int	run_command(char **argv, char **envp, int index)
{
	int		i;
	char	*path_variable;
	char	*full_path;
	char	*full_path_with_command;
	char	**split_variable;
	char	**command_with_arguments;
	char	*command;

	path_variable = NULL;
	while (*envp)
	{
		if (strncmp(*envp, "PATH=", 5) == 0)
		{
			path_variable = *envp + 5;
			break ;
		}
		envp++;
	}
	if (!path_variable)
	{
		ft_printf("PATH variable not found.\n");
		return (1);
	}
	split_variable = ft_split(path_variable, ':');
	command_with_arguments = ft_split(argv[index], ' ');
	command = command_with_arguments[0];
	i = 0;
	while (split_variable[i])
	{
		full_path = ft_strjoin(split_variable[i], "/");
		full_path_with_command = ft_strjoin(full_path, command);
		free((void **)full_path);
		if (access(full_path_with_command, X_OK) == 0)
		{
			execve(full_path_with_command, command_with_arguments, envp);
			perror("Failed to execute command");
		}
		free((void **)full_path_with_command);
		i++;
	}
	ft_printf("Command not found.\n");
	free_2d_array((void **)command_with_arguments);
	free_2d_array((void **) split_variable);
	return (0);
}
