/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_handling_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: upolat <upolat@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 14:09:53 by upolat            #+#    #+#             */
/*   Updated: 2024/05/30 11:07:15 by upolat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

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

pid_t	**pids_malloc (int argc, int heredoc_exists)
{
	int		i;
	int		num_iterations;
	pid_t	**pids;

	num_iterations = argc - 4 - heredoc_exists;
	pids = malloc(num_iterations * sizeof(pid_t *));
	if (!pids)
	{
		perror("Failed to allocate memory for pid pointers");
		return (0);
	}
	i = 0;
	while (i < num_iterations)
	{
		pids[i] = malloc(2 * sizeof(pid_t));
		if (!pids[i])
		{
			perror("Failed to allocate memory for pid pointers");
			free_2d_array((void **)pids);
			return (0);
		}
		i++;
	}
	return(pids);
}
