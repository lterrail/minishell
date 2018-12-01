/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lterrail <lterrail@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/23 12:24:32 by lterrail          #+#    #+#             */
/*   Updated: 2018/12/01 18:47:30 by lterrail         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int		ft_parse_builtins(t_ms *ms, char *line)
{
	if (!ft_strcmp(ms->first_argc, "exit"))
		ft_exit(ms, NULL, NULL);
	else if (!ft_strncmp(ms->first_argc, "cd", ft_strlen(ms->first_argc)))
		ft_init_cd(ms, ft_epur_line(line, 2));
	else if (!ft_strcmp(ms->first_argc, "unsetenv"))
		ms->env = ft_unsetenv(ms, ft_epur_line(line, 8), ms->env);
	else if (!ft_strcmp(ms->first_argc, "setenv"))
		ms->env = ft_setenv(ms, ft_epur_line(line, 6), 0, ms->env);
	else if (!ft_strcmp(ms->first_argc, "env"))
		ft_parse_env(ms, ft_epur_line(line, 3), ms->env);
	else if (!ft_strcmp(ms->first_argc, "echo"))
	{
		ft_printf("%s\n", &line[4]);
	}
	else
		return (0);
	return (1);
}

static void		ft_parse_cmd(t_ms *ms, char *line)
{
	char	*path;

	path = NULL;
	if (!ft_strcmp(ms->first_argc, "path"))
		ft_print_paths(ms);
	else if ((path = ft_search_valid_builtin(ms)))
	{
		if (ft_strstr(path, "cat"))
			g_reset_input = 1;
		ft_exec_cmd(ms, path, line, ms->env);
		free(path);
	}
	else if (!path)
		ft_exec_cmd_with_path(ms, ms->first_argc, line, ms->env);
	else
		ft_printf("{red}%s: Command not found{eoc}\n", ms->first_argc);
}

int				ft_parser(t_ms *ms, char *line)
{
	cmd_parser_echaper(line);
	cmd_parser_interpret_quot(line);
	if (!line)
		return (E_ERROR);
	ft_get_first_argc(ms, line);
	if (!ft_parse_builtins(ms, line))
		ft_parse_cmd(ms, line);
	free(ms->first_argc);
	return (E_SUCCESS);
}
