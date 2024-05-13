/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: upolat <upolat@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 22:28:18 by upolat            #+#    #+#             */
/*   Updated: 2024/05/12 20:42:42 by upolat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include "ft_printf.h"
#include "libft.h"

int	run_command(char **argv, char **envp, int index);

void	free_2d(char **arr)
{
	int i;

	i = 0;
	while (arr[i])
		free(arr[i++]);
	free(arr);
}

int	main(int argc, char **argv, char **envp)
{
	int		infile_fd;
	int		outfile_fd;
	int		pipe_fd[2];
	pid_t	pid1;
	int		i;

	
	if (argc < 5)
	{
		ft_printf("Not enough parameters.");
		return (1);
	}

	i = 2;

	// Open the input file
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
		return (1);
	}
	
	if (pipe(pipe_fd) == -1)
	{
		perror("pipe");
		return (1);
	}

	pid1 = fork();
	if (pid1 == 0)
	{
		// Inside the first child process
		dup2(infile_fd, STDIN_FILENO); // input source is redirected to infile
		dup2(pipe_fd[1], STDOUT_FILENO); // output target is redirected to pipe
		close(pipe_fd[0]); // close unused read end of the pipe in child
		close(pipe_fd[1]); // close write end of the pipe because it is not needed after dup2
		close(infile_fd);  // already duplicated
		run_command(argv, envp, i);
	}
	else
	{
		waitpid(pid1, NULL, 0); // Wait for the first child to complete
		dup2(pipe_fd[0], STDIN_FILENO); // input from pipe
		dup2(outfile_fd, STDOUT_FILENO); // output to file
		close(pipe_fd[1]); // close write end of the pipe in parent
		close(pipe_fd[0]); // not needed after dup2
		close(outfile_fd); // already duplicated
		run_command(argv, envp, i + 1);
	}
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
		free(full_path);
		if (access(full_path_with_command, X_OK) == 0)
		{
			execve(full_path_with_command, command_with_arguments, envp);
			perror("Failed to execute command");
		}
		free(full_path_with_command);
		i++;
	}
	ft_printf("Command not found.\n");
    free_2d(command_with_arguments);
    free_2d(split_variable);
	return (0);
}
