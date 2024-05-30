/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: upolat <upolat@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 18:47:15 by upolat            #+#    #+#             */
/*   Updated: 2024/05/30 15:26:45 by upolat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include <stdio.h>
# include <unistd.h>
# include <string.h>
# include <fcntl.h>
# include "libft/libft.h"

typedef struct s_vars
{
	int		infile_fd;
	int		outfile_fd;
	int		*pipes;
	int		pipe_amount;
	int		command_amount;
	int		here_doc;
	pid_t	**pid;
	char	*path_variable;
	char	*full_path;
	char	*full_path_with_command;
	char	**split_variable;
	char	**command_with_arguments;
	char	*command;
}	t_vars;

int		handle_here_doc(int argc, char *argv2);
void	free_2d_array(void **arr);
int		**fd_malloc(int argc, int heredoc_exists);
void	close_and_free(int **fd, int infile_fd, int outfile_fd, int argc, int heredoc_exists);
int		run_command(char **argv, char **envp, int index);
char	**ft_split_3(char *str);
int		error_handler(char *str1, char *str2);

#endif
