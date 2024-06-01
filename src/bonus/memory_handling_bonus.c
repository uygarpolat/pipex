/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_handling_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: upolat <upolat@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 14:09:53 by upolat            #+#    #+#             */
/*   Updated: 2024/06/01 22:50:50 by upolat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/pipex_bonus.h"

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

void	fd_malloc(t_vars *t)
{
	int	i;

	i = 0;
	t->fd = malloc(sizeof(int *) * (t->pipe_amount + 1));
	if (t->fd == NULL)
		return ; // <------------------------------------- Enter a proper error
	while (i < t->pipe_amount)
	{
		t->fd[i] = malloc(sizeof(int) * 2);
		if (t->fd[i] == NULL)
		{
			free_2d_array((void **)t->fd);
			return ; // <------------------------------------- Enter a proper error
		}
		i++;
	}
	t->fd[i] = 0;
	return ;
}

void	pids_malloc (t_vars *t)
{
	int		i;

	t->pid = malloc((t->pipe_amount + 1) * sizeof(pid_t *));
	if (!t->pid)
	{
		perror("Failed to allocate memory for pid pointers");
		return ; //<------------------------------------- Enter a proper error
	}
	i = 0;
	while (i < t->pipe_amount)
	{
		t->pid[i] = malloc(2 * sizeof(pid_t));
		if (!t->pid[i])
		{
			perror("Failed to allocate memory for pid pointers");
			free_2d_array((void **)t->pid);
			return ; // <------------------------------------- Enter a proper error
		}
		i++;
	}
	t->pid[i] = 0;
	return ;
}
