/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_and_free_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: upolat <upolat@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 14:41:06 by upolat            #+#    #+#             */
/*   Updated: 2024/06/01 20:05:08 by upolat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/pipex_bonus.h"

void	close_and_free(t_vars *t)
{
	int	i;

	i = 0;
	close(t->infile_fd);
	close(t->outfile_fd);
	while (i < t->pipe_amount)
	{
		close(t->fd[i][0]);
		close(t->fd[i][1]);
		i++;
	}
	free_2d_array((void **)t->fd);
}
