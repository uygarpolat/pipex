/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: upolat <upolat@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 09:12:56 by upolat            #+#    #+#             */
/*   Updated: 2024/06/05 23:39:23 by upolat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include "../../include/pipex_bonus.h"

int	handle_here_doc(int argc, char *argv2, t_vars *t)
{
	int		n;
	char	*str;

	t->here_doc_fd = open(".here_doc", O_CREAT | O_WRONLY | O_TRUNC, 0644);
	while (1)
	{
		n = argc;
		while (n-- > 5)
			write(STDOUT_FILENO, "pipe ", 5);
		write(STDOUT_FILENO, "heredoc> ", 9);
		str = get_next_line(STDIN_FILENO);
		if (!str)
			break ;
		if (!ft_strncmp(str, argv2, ft_strlen(argv2))
			&& str[ft_strlen(argv2)] == '\n')
			break ;
		// Do I need to free str before exiting and after encountering one
		// of the two if conditions above? Answer is confirmed yes.
		// You can do it here, or after the while loop: if (buf), free (str).
		ft_putstr_fd(str, t->here_doc_fd);
		free(str);
		str = NULL;
	}
	close(t->here_doc_fd);
	t->here_doc_fd = -1;
	t->here_doc_fd = open(".here_doc", O_RDONLY);
	return (t->here_doc_fd);
	// Are you utilizing the return value elsewhere when it is negative, indicating a failed opening?
}
