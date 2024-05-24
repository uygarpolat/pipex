/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: upolat <upolat@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 09:12:56 by upolat            #+#    #+#             */
/*   Updated: 2024/05/23 23:03:36 by upolat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include "pipex_bonus.h"

int	handle_here_doc(char *argv2)
{
	int		fd;
	int		fd2;
	char	*str;

	fd = open(".here_doc", O_CREAT | O_WRONLY | O_TRUNC, 0644);

	while (1)
	{
		write(STDOUT_FILENO, "heredoc> ", 9);
		str = get_next_line(STDIN_FILENO);
		if (!str)
			break ;
		if (!ft_strncmp(str, argv2, ft_strlen(argv2)) && str[ft_strlen(argv2)] == '\n')
			break ;
		write(fd, str, ft_strlen(str));
		free(str);
	}
	close(fd);
	fd2 = open(".here_doc", O_RDONLY);
	return (fd2);
}
