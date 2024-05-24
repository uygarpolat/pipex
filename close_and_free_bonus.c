/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_and_free_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: upolat <upolat@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 14:41:06 by upolat            #+#    #+#             */
/*   Updated: 2024/05/24 14:44:35 by upolat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

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
