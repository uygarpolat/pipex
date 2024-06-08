/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: upolat <upolat@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 18:47:15 by upolat            #+#    #+#             */
/*   Updated: 2024/06/08 12:11:11 by upolat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include <string.h>
# include <unistd.h>
# include <errno.h>
# include <fcntl.h>
# include <sys/wait.h>
# include "../libft/libft.h"

typedef struct s_vars
{
	char	**envp;
	int		infile_fd;
	int		outfile_fd;
	int		**fd;
	int		pipe_amount;
	int		command_amount;
	int		here_doc;
	int		here_doc_fd;
	pid_t	**pid;
	char	*path_variable;
	char	*full_path_with_command;
	char	**split_variable;
	char	**command_with_arguments;
	char	*command;
}	t_vars;

// Handle error
void	error_handler1(char *str, t_vars *t, char *str2, int errorcode);
void	error_handler2(char *str, t_vars *t, int errnum, int errorcode);
void	close_and_free(t_vars *t);
void	close_free_exit(t_vars *t, int exitcode);

// Handle memory
void	free_2d_array(void ***arr);
void	fd_malloc(t_vars *t);
void	pids_malloc(t_vars *t);

// Handle FDs and pipes and PATH
void	open_infile(int argc, char **argv, t_vars *t);
void	open_outfile(int argc, char **argv, t_vars *t);
void	create_pipes(t_vars *t);
char	*get_path(char **envp);

// Handle forks
void	handle_fork(int argc, char **argv, t_vars *t);

// Handle execution of the command
int		run_command(char **argv, t_vars *t, int index);

// Handle here_doc
int		handle_here_doc(int argc, char *argv2, t_vars *t);

#endif
