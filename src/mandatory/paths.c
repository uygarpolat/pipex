/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paths_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: upolat <upolat@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 14:35:41 by upolat            #+#    #+#             */
/*   Updated: 2024/06/07 10:54:26 by upolat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/pipex_bonus.h"

char	*get_path2(char **envp)
{
	if (!envp)
		return (NULL);
	while (*envp)
	{
		if (strncmp(*envp, "PATH=", 5) == 0)
			return (*envp + 5);
		envp++;
	}
	//if (*envp == NULL)
	return (NULL);
}
