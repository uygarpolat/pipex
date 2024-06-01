/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handler_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: upolat <upolat@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 14:23:58 by upolat            #+#    #+#             */
/*   Updated: 2024/06/01 00:12:07 by upolat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	error_handler3(char *str, int errnum, int errorcode)
{
    ft_putstr_fd("pipex: ", 2);
    ft_putstr_fd(str, 2);
    ft_putstr_fd(": ", 2);
    ft_putstr_fd(strerror(errnum), 2);
	ft_putstr_fd("\n", 2);
    exit(errorcode);
}

/*
void	error_handler4(t_vars *t, int exitcode)
{
	if (t->infilei_fd >= 0)
		close(t->infile);
	if (t->outfile_fd >= 0)
		close(t->outfile);
	if (t->here_doc_fd >= 0)
		close(t->here_fd);
	if (t->paths)
		free_ptr_arr(t->paths);
	if (t->pid)
		free(t->pid);
	if (t->pipes)
		free(t->pipes);
	if (t->cmd_path)
		free(t->cmd_path);
	if (t->args)
		free(t->args);
	if (access(".here_doc", F_OK) == 0)
		unlink(".here_doc");
	exit(exitcode);
}
*/
