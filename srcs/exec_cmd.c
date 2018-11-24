/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lterrail <lterrail@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/23 20:23:47 by lterrail          #+#    #+#             */
/*   Updated: 2018/11/24 12:52:21 by lterrail         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void		ft_exec_cmd(t_ms *ms, char *cmd, int flag)
{
	char	*tmp;
	char	*path;

	path = NULL;
	tmp = NULL;
	if (!flag && !(tmp = ft_strdup("/bin")))
		ft_exit(ms, NULL, "Failed to malloc in ft_exec_cmd");
	if (!flag && ft_search_cmd_in_paths(ms, tmp))
	{
		if (!(path = ft_strjoin(tmp, cmd)))
			ft_exit(ms, tmp, "Failed to malloc in ft_exec_cmd");
		free(tmp);
		if ((execve(path, ms->options, NULL)) == -1)
			ft_exit(ms, NULL, "Failed to execve the program");
	}
	else if ((execve(cmd, ms->options, NULL)) == -1)
		ft_exit(ms, tmp, "Failed to execve the program");
	else
		ft_printf("{red}Can't find the path /bin in env{eoc}\n");
}

int				ft_init_exec_cmd(t_ms *ms, char *cmd, char *line, int flag)
{
	if (!(ms->options = ft_strsplit(line, ' ')))
		ft_exit(ms, line, "Failed to create ms->options");
	if (!flag && !(ft_find_and_copy_paths(ms, ms->env)))
	{
		ft_free_tab(ms->options, -1);
		ms->options = NULL;
		ft_printf("{red}Can't find the path /bin in env{eoc}\n");
		return (E_ERROR);
	}
	ft_exec_cmd(ms, cmd, flag);
	ft_free_tab(ms->options, -1);
	ms->options = NULL;
	ft_free_tab(ms->paths, -1);
	ms->paths = NULL;
	return (E_SUCCESS);
}
