/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lterrail <lterrail@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/24 17:02:03 by lterrail          #+#    #+#             */
/*   Updated: 2018/11/24 18:58:52 by lterrail         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>

char		*ft_get_pwd(void)
{
	char        current_dir[PATH_MAX];
	char        *ptr;

	ptr = NULL;
	bzero(current_dir, PATH_MAX);
	if (!(ptr = getcwd(current_dir, PATH_MAX)))
		return (EXIT_SUCCESS);
	printf("%s ", ptr);
	// printf("%p\n", buf);
	// printf("%p\n", pwd);
	return (ptr);
}

void		ft_exec_cd(t_ms *ms, char *line)
{
	(void)ms;
	(void)line;
}
