/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_files_and_pipes.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: upolat <upolat@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 13:42:31 by upolat            #+#    #+#             */
/*   Updated: 2024/06/08 14:16:55 by upolat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/pipex.h"

void	open_infile(char **argv, t_vars *t)
{
	if (access(argv[1], F_OK) == -1 || access(argv[1], R_OK) == -1)
		error_handler2(argv[1], t, errno, EXIT_FAILURE);
	t->infile_fd = open(argv[1], O_RDONLY);
	if (t->infile_fd == -1)
		error_handler2(argv[1], t, errno, EXIT_FAILURE);
}

void	open_outfile(int argc, char **argv, t_vars *t)
{
	if (access(argv[argc - 1], W_OK) == -1)
	{
		if (errno == EACCES)
			error_handler2(argv[argc - 1], t, errno, EXIT_FAILURE);
	}
	t->outfile_fd = open(argv[argc - 1], O_TRUNC | O_CREAT | O_RDWR, 0644);
	if (t->outfile_fd == -1)
		error_handler2(argv[argc - 1], t, errno, EXIT_FAILURE);
}

void	create_pipes(t_vars *t)
{
	int	i;

	i = 0;
	while (i < t->pipe_amount)
	{
		t->fd[i][0] = -42;
		t->fd[i][1] = -42;
		if (pipe(t->fd[i]) == -1)
			error_handler2("Pipe function failed!", t, errno, EXIT_FAILURE);
		i++;
	}
}

char	*get_path(char **envp)
{
	if (!envp)
		return (NULL);
	while (*envp)
	{
		if (strncmp(*envp, "PATH=", 5) == 0)
			return (*envp + 5);
		envp++;
	}
	return (NULL);
}
