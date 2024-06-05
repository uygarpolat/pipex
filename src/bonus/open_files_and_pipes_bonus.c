/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_files_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: upolat <upolat@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 13:42:31 by upolat            #+#    #+#             */
/*   Updated: 2024/06/05 12:38:19 by upolat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/pipex_bonus.h"

void	open_infile(int argc, char **argv, t_vars *t)
{
	if (t->here_doc == 0 && (access(argv[1], F_OK) == -1
			|| access(argv[1], R_OK) == -1))
		error_handler3(argv[1], t, errno, EXIT_FAILURE);
	if (t->here_doc == 1)
		t->infile_fd = handle_here_doc(argc, argv[2], t);
	else
		t->infile_fd = open(argv[1], O_RDONLY);
	if (t->infile_fd < 0)
		error_handler3(argv[1 + t->here_doc], t, errno, EXIT_FAILURE);
}

void	open_outfile(int argc, char **argv, t_vars *t)
{
	if (access(argv[argc - 1], W_OK) == -1)
	{
		if (errno == EACCES)
			error_handler3(argv[argc - 1], t, errno, EXIT_FAILURE);
	}
	if (t->here_doc == 1)
		t->outfile_fd = open(argv[argc - 1], O_APPEND | O_CREAT | O_RDWR, 0644);
	else
		t->outfile_fd = open(argv[argc - 1], O_TRUNC | O_CREAT | O_RDWR, 0644);
	if (t->outfile_fd < 0)
		error_handler3(argv[argc - 1], t, errno, EXIT_FAILURE);
}

void	create_pipes(t_vars *t)
{
	int	i;

	i = 0;
	while (i < t->pipe_amount)
	{
		if (pipe(t->fd[i]) == -1)
		{
			close_and_free(t);
			error_handler3("Enter a proper error handling function here!!!!!!!!!!!", t, errno, EXIT_FAILURE); // -----> Is EXIT_FAILURE correct here?
		}
		i++;
	}
}
