/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lterrail <lterrail@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/23 12:24:32 by lterrail          #+#    #+#             */
/*   Updated: 2018/11/26 19:06:12 by lterrail         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

static char		*ft_check_access(t_ms *ms)
{
	int		i;
	char	*path;
	char	*tmp;

	i = -1;
	path = NULL;
	tmp = NULL;
	if (!(tmp = ft_strjoin("/", ms->first_argc)))
		ft_exit(ms, NULL, "Failed to malloc in ft_check_access");
	if (ft_find_and_copy_paths(ms, ms->env))
	{
		while (ms->paths[++i])
		{
			if (!(path = ft_strjoin(ms->paths[i], tmp)))
				ft_exit(ms, NULL, "Failed to malloc in ft_check_access");
			if ((access(path, F_OK)) == 0)
			{
				free(tmp);
				return (path);
			}
			free(path);
		}
	}
	free(tmp);
	return (NULL);
}

static char		*ft_check_line(char *line, int len)
{
	int		i;

	i = len;
	while (line[i] && (line[i] == ' ' || line[i] == '\t'))
		i++;
	if (line[i])
		return (&line[i]);
	return (NULL);
}

int				ft_parse_cmd(t_ms *ms, char *line)
{
	char	*path;
	char	*tmp;

	tmp = line;
	path = NULL;
	line = ft_check_line(line, 0);
	if (!line)
		return (E_ERROR);
	ft_get_first_argc(ms, line);
	if (!ft_strcmp(ms->first_argc, "exit"))
		ft_exit(ms, line, NULL);
	else if (!ft_strcmp(ms->first_argc, "cd"))
		ft_init_cd(ms, ft_check_line(line, 2));
	else if (!ft_strcmp(ms->first_argc, "unsetenv"))
		ft_unsetenv(ms, ft_check_line(line, 8));
	else if (!ft_strcmp(ms->first_argc, "setenv"))
		ft_setenv(ms, ft_check_line(line, 6));
	else if (!ft_strcmp(ms->first_argc, "env"))
		ft_print_env(ms);
	else if (!ft_strcmp(ms->first_argc, "echo"))
	{
		if ((line = ft_check_line(line, 4)))
			ft_printf("%s\n", line);
	}
	else if (!ft_strcmp(ms->first_argc, "path"))
		ft_print_paths(ms);
	else if ((path = ft_check_access(ms)))
		ft_exec_cmd(ms, path, line);
	else if (!path)
		ft_exec_cmd_with_path(ms, ms->first_argc, line);
	else
		ft_printf("{red}%s: Command not found{eoc}\n", ms->first_argc);
	free(ms->first_argc);
	if (path)
		free(path);
	free(tmp);
	return (E_SUCCESS);
}
