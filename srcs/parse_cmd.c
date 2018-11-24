/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lterrail <lterrail@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/23 12:24:32 by lterrail          #+#    #+#             */
/*   Updated: 2018/11/24 12:52:18 by lterrail         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*

execve = binaire, path, NULL;

pid_t	pid;

if ((pid = fork()) == -1)
	ft_exit(paths, tmp, "Failed to fork");
	wait(&pid);
*/

static void		ft_print_paths(t_ms *ms)
{
	int		i;

	i = -1;
	if (ft_find_and_copy_paths(ms, ms->env))
	{
		while (ms->paths[++i])
			ft_printf("%s\n", ms->paths[i]);
		ft_free_tab(ms->paths, -1);
		ms->paths = NULL;
	}
	else
		ft_printf("{red}PATH=/ Not found{eoc}\n");
}

static void		ft_get_first_argc(t_ms *ms, char *line)
{
	int		i;

	if (!(ms->first_argc = ft_strdup(line)))
		ft_exit(ms, line, "Failed to create ms->argc");
	i = 0;
	while (ms->first_argc[i] && ft_iscmd(ms->first_argc[i]))
		i++;
	ms->first_argc[i] = '\0';
}

int				ft_parse_cmd(t_ms *ms, char *line)
{
	ft_get_first_argc(ms, line);
	if (!ft_strcmp(ms->first_argc, "ls"))
		ft_init_exec_cmd(ms, "/ls", line, 0);
	else if (ft_strstr(ms->first_argc, "ls"))
		ft_init_exec_cmd(ms, ms->first_argc, line, 1);
	else if (!ft_strcmp(ms->first_argc, "pwd"))
		ft_init_exec_cmd(ms, "/pwd", line, 0);
	else if (!ft_strcmp(ms->first_argc, "exit"))
		ft_exit(ms, line, NULL);
	else if (!ft_strcmp(ms->first_argc, "unsetenv"))
		ft_unsetenv(ms, &line[9]);
	else if (!ft_strcmp(ms->first_argc, "setenv"))
		ft_setenv(ms, &line[7]);
	else if (!ft_strcmp(ms->first_argc, "env"))
		ft_print_env(ms);
	else if (!ft_strcmp(ms->first_argc, "echo"))
		ft_printf("%s\n", &line[5]);
	else if (!ft_strcmp(ms->first_argc, "path"))
		ft_print_paths(ms);
	else
		ft_printf("{red}%s: Command not found{eoc}\n", ms->first_argc);
	free(ms->first_argc);
	return (E_SUCCESS);
}
