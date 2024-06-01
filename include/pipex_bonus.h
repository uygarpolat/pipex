/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: upolat <upolat@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 18:47:15 by upolat            #+#    #+#             */
/*   Updated: 2024/06/01 19:19:25 by upolat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include <stdio.h>
# include <string.h>
# include <unistd.h>
# include <errno.h>
# include <fcntl.h>
# include <sys/wait.h>
# include "../libft/libft.h"

typedef struct s_vars
{
	char	**envp;
	int		infile_fd; //SET
	int		outfile_fd; //SET
	int		**fd;
	int		pipe_amount; //SET
	int		command_amount; // SET
	int		here_doc; //SET
	int		here_doc_fd;
	pid_t	**pid; //SET
	char	*path_variable; //SET, was path_string, but you need to seperate path finder code from command runner code.
	//char	*full_path; //THIS DOESN'T LOOK LIKE IT SHOULD BE IN THE STRUCT
	char	*full_path_with_command; //SET, was cmd_path
	char	**split_variable; // paths
	char	**command_with_arguments; //SET, was args
	char	*command; // SET inside of function run command (the location might have changed since last edit)
}	t_vars;

void	initialize_t_vars(t_vars *t, char **argv, char **envp);
int		handle_here_doc(int argc, char *argv2, t_vars *t);
void	free_2d_array(void **arr);
void	fd_malloc(t_vars *t);
void	close_and_free(t_vars *t);
int		run_command(char **argv, t_vars *t, int index);
char	**ft_split_3(char *str);
void	error_handler3(char *str, int errnum, int errorcode);
char	*get_path2(char **envp);

void	initialize_t_vars(t_vars *t, char **argv, char **envp);
void	handle_fork(int argc, char **argv, t_vars *t);
void	pids_malloc (t_vars *t);
void	open_infile(int argc, char **argv, t_vars *t);
void	open_outfile(int argc, char **argv, t_vars *t);
void	first_child_fork(int argc, char **argv, t_vars *t, int i);
void	second_child_fork(int argc, char **argv, t_vars *t, int i);
int		pid_wait(pid_t pid);


#endif
