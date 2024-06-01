/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: upolat <upolat@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 09:12:56 by upolat            #+#    #+#             */
/*   Updated: 2024/06/01 20:06:51 by upolat           ###   ########.fr       */
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
		if (!ft_strncmp(str, argv2, ft_strlen(argv2)) && str[ft_strlen(argv2)] == '\n')
			break ;
		ft_putstr_fd(str, t->here_doc_fd);
		//write(heredoc_fd, str, ft_strlen(str));
		free(str);
	}
	close(t->here_doc_fd);
	t->here_doc_fd = open(".here_doc", O_RDONLY); // Is it ok to recycle fd like this? If it works, that's a good enough test.
	return (t->here_doc_fd);
}
