/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: upolat <upolat@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 09:12:56 by upolat            #+#    #+#             */
/*   Updated: 2024/06/07 23:33:33 by upolat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/pipex_bonus.h"

int	handle_here_doc(int ac, char *av2, t_vars *t)
{
	int		n;
	char	*s;

	t->here_doc_fd = open(".here_doc", O_CREAT | O_WRONLY | O_TRUNC, 0644);
	while (1)
	{
		n = ac;
		while (n-- > 5)
			write(STDOUT_FILENO, "pipe ", 5);
		write(STDOUT_FILENO, "heredoc> ", 9);
		s = get_next_line(STDIN_FILENO);
		if (!s)
			break ;
		if (!ft_strncmp(s, av2, ft_strlen(av2)) && s[ft_strlen(av2)] == '\n')
			break ;
		ft_putstr_fd(s, t->here_doc_fd);
		free(s);
		s = NULL;
	}
	if (s)
		free(s);
	close(t->here_doc_fd);
	t->here_doc_fd = -1;
	t->here_doc_fd = open(".here_doc", O_RDONLY);
	return (t->here_doc_fd);
}
