/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_handling_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: upolat <upolat@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 14:09:53 by upolat            #+#    #+#             */
/*   Updated: 2024/05/24 14:40:47 by upolat           ###   ########.fr       */
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
