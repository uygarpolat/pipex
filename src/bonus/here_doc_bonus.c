/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: upolat <upolat@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 09:12:56 by upolat            #+#    #+#             */
/*   Updated: 2024/06/12 11:19:58 by upolat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/pipex_bonus.h"

int	handle_here_doc(char *v, t_vars *t)
{
	char	*s;

	t->here_doc_fd = open(".here_doc", O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (t->here_doc_fd == -1)
		error_handler2("here_doc failed to open", t, errno, EXIT_FAILURE);
	while (1)
	{
		ft_putstr_fd("> ", STDIN_FILENO);
		s = get_next_line(STDIN_FILENO);
		if (!s || (!ft_strncmp(s, v, ft_strlen(v)) && s[ft_strlen(v)] == '\n'))
			break ;
		ft_putstr_fd(s, t->here_doc_fd);
		free(s);
		s = NULL;
	}
	if (s)
		free(s);
	close(t->here_doc_fd);
	t->here_doc_fd = -42;
	t->here_doc_fd = open(".here_doc", O_RDONLY);
	return (t->here_doc_fd);
}
