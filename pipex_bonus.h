/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: upolat <upolat@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 18:47:15 by upolat            #+#    #+#             */
/*   Updated: 2024/05/24 16:41:31 by upolat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include <stdio.h>
# include <unistd.h>
# include <string.h>
# include <fcntl.h>
# include "libft/libft.h"

typedef struct s_fds
{
	int	infile_fd;
	int	outfile_fd;
}	t_fds;

int		handle_here_doc(char *argv2);
void	free_2d_array(void **arr);
int		**fd_malloc(int argc, int heredoc_exists);
void	close_and_free(int **fd, int infile_fd, int outfile_fd, int argc, int heredoc_exists);
int		run_command(char **argv, char **envp, int index);

#endif
