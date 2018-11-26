/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lterrail <lterrail@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/23 20:23:47 by lterrail          #+#    #+#             */
/*   Updated: 2018/11/26 17:56:20 by lterrail         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		ft_exec_cmd(t_ms *ms, char *path, char *line)
{
	pid_t	father;
	int		ret;

	ret = 0;
	if (!(ms->options = ft_strsplit(line, ' ')))
	{
		free(path);
		ft_exit(ms, line, "Failed to create ms->options");
	}
	if ((father = fork()) == -1)
		ft_exit(ms, path, "Failed to fork");
	if (father > 0)
		wait(&father);
	else if (father == 0)
	{
		if ((ret = execve(path, ms->options, ms->env)) == -1)
		{
			free(path);
			ft_exit(ms, line, "Failed to execve the program");
		}
		exit(ret);
	}
	ft_free_tab(ms->options, -1);
	ms->options = NULL;
}

static int            exec_chmod(char *path)
{
	struct stat    stat;

	lstat(path, &stat);
	if (S_ISLNK(stat.st_mode) == 1)
		return (0);
	else if (S_ISFIFO(stat.st_mode) == 1)
		return (0);
	else if (S_ISBLK(stat.st_mode) == 1)
		return (0);
	else if (S_ISCHR(stat.st_mode) == 1)
		return (0);
	else if (S_ISSOCK(stat.st_mode) == 1)
		return (0);
	else if (S_ISDIR(stat.st_mode) == 1)
		return (0);
	return (1);
}

void		ft_exec_cmd_with_path(t_ms *ms, char *path, char *line)
{
	struct stat	stat;

	if (lstat(path, &stat) == -1 || !exec_chmod(path))
		ft_printf("{red}No such file or directory{eoc}\n");
	else
		ft_exec_cmd(ms, path, line);
}
