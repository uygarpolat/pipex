/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_files_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: upolat <upolat@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 13:42:31 by upolat            #+#    #+#             */
/*   Updated: 2024/06/02 00:07:01 by upolat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/pipex_bonus.h"

void	open_infile(int argc, char **argv, t_vars *t)
{
	if (t->here_doc == 1)
		t->infile_fd = handle_here_doc(argc, argv[2], t);
	else
	{
		t->infile_fd = open(argv[1], O_RDONLY);
		/*if (t->infile < 0)
		{
			ft_putstr_fd("pipex: ", 2);
			ft_putstr_fd(argv[1], 2);
			ft_putstr_fd(": ", 2);
			perror("");
			close_pipes(t);
			error_exit4(t, 1);
		}*/
		if (t->infile_fd < 0)
		{
			//close_and_free(t); // ------------------------------------------------------> This needs to come after error_handler3 somehow. Otherwise I am getting "bad file descriptor" error on pipex tester, which isn't matching Bash output. Also check the contents of close_and_free. It hasn't been updated in a while.
			error_handler3(argv[1], t, errno, 1);
		}
	}
}

void	open_outfile(int argc, char **argv, t_vars *t)
{
	if (t->here_doc == 1)
		t->outfile_fd = open(argv[argc - 1], O_APPEND | O_CREAT | O_RDWR, 0644);
	else
		t->outfile_fd = open(argv[argc - 1], O_TRUNC | O_CREAT | O_RDWR, 0644);
/*	if (t->outfile < 0)
	{
		ft_putstr_fd("pipex: ", 2);
		ft_putstr_fd(argv[argc - 1], 2);
		ft_putstr_fd(": ", 2);
		perror("");
		close_pipes(t);
		error_exit4(t, 1);
	}*/
	if (t->outfile_fd < 0)
	{	
		//close_and_free(t);  // ------------------------------------------------------> This needs to come after error_handler3 somehow. Otherwise I am getting "bad file descriptor" error on pipex tester, which isn't matching Bash output. Also check the contents of close_and_free. It hasn't been updated in a while.
		error_handler3(argv[argc - 1], t, errno, 1);
	}
/*	if (write(t->outfile_fd, "", 0) < 0) // writing 0 bytes to test if write permission exists, so that pipex tester is satisfied
	{
		error_handler3(argv[argc - 1], errno, 1);
		// CLOSE PIPES!
	}*/
}
