/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_handling_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: upolat <upolat@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 14:09:53 by upolat            #+#    #+#             */
/*   Updated: 2024/06/05 21:25:11 by upolat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/pipex_bonus.h"

void	free_2d_array(void ***arr)
{
	int	i;

	i = 0;
	if (!*arr)
		return ;
	while ((*arr)[i])
	{
		free((*arr)[i]);
		(*arr)[i] = NULL;
		i++;
	}
	free(*arr);
	*arr = NULL;
}

void	fd_malloc(t_vars *t)
{
	int	i;

	i = 0;
	t->fd = malloc(sizeof(int *) * (t->pipe_amount + 1));
	if (t->fd == NULL)
	{
		perror("Failed to allocate memory for file descriptors");
		exit(EXIT_FAILURE); // CHANGE THIS AND ALL 4 EXIT STATEMENT IN THIS FILE TO ERROR_HANDLER FUNCTION!
	}
	while (i < t->pipe_amount)
	{
		t->fd[i] = malloc(sizeof(int) * 2);
		if (t->fd[i] == NULL)
		{
			free_2d_array((void ***)&t->fd);
			perror("Failed to allocate memory for file descriptors");
			exit(EXIT_FAILURE);
		}
		i++;
	}
	t->fd[i] = NULL;
}

void	pids_malloc(t_vars *t)
{
	int	i;

	t->pid = malloc((t->pipe_amount + 1) * sizeof(pid_t *));
	if (!t->pid)
	{
		perror("Failed to allocate memory for PID");
		exit(EXIT_FAILURE);
	}
	i = 0;
	while (i < t->pipe_amount)
	{
		t->pid[i] = malloc(2 * sizeof(pid_t));
		if (!t->pid[i])
		{
			free_2d_array((void ***)&t->pid);
			perror("Failed to allocate memory for PID");
			exit(EXIT_FAILURE);
		}
		i++;
	}
	t->pid[i] = NULL;
}
