/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lterrail <lterrail@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/24 17:02:03 by lterrail          #+#    #+#             */
/*   Updated: 2018/11/26 20:28:18 by lterrail         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void		ft_parse_cd(t_ms *ms, char *argcs)
{
	ft_printf("%s\n", argcs);
	if (!ft_strcmp(argcs, ".."))
		ft_del_last_argc(ms);
	else if (!ft_strcmp(argcs, "-"))
		ft_swap_argcs(ms);
	else if (!ft_strcmp(argcs, "~") || !argcs)
		ft_get_home(ms);
	else
		ft_add_argc(ms, argcs);
}

static void		ft_chdir(t_ms *ms)
{
	int		i;

	i = ft_find_env_variable(ms, "PWD=");
	if (!chdir(ms->pwd) && ms->error == 0)
	{
		free(ms->env[i]);
		if (!(ms->env[i] = ft_strjoin("PWD=", ms->pwd)))
			ft_exit(ms, NULL, "Failed to malloc");
	}
	else
		ft_printf("{red}No such file or directory{eoc}\n");
}

static int		ft_solve_one_argc_cd(t_ms *ms, char *line)
{
	char	cwd[1024];

	if (!line)
	{
		ft_get_home(ms);
		ft_chdir(ms);
		return (E_ERROR);
	}
	if (line[0] != '-' || ms->first_call == 1)
	{
		if (!(ms->pwd = ft_strdup(getcwd(cwd, sizeof(cwd)))))
			ft_exit(ms, line, "Failed to malloc");
		if (!(ms->old_pwd = ft_strdup(getcwd(cwd, sizeof(cwd)))))
			ft_exit(ms, line, "Failed to malloc");
		ms->first_call = 0;
	}
	else if (line[0] == '/')
		ms->pwd = ft_strdup("/");
	else if (!ft_strcmp(line, "."))
		return (E_ERROR);
	return (E_SUCCESS);
}

void			ft_init_cd(t_ms *ms, char *line)
{
	char	**argcs;
	int		i;

	i = 0;
	argcs = NULL;
	ms->error = 0;
	if (!ft_find_env_variable(ms, "PWD="))
	{
		ft_printf("{red} variable PWD=/ doesn't exist{eoc}\n");
		return ;
	}
	if (!ft_solve_one_argc_cd(ms, line))
		return ;
	if (!(argcs = ft_strsplit(line, '/')))
		ft_exit(ms, line, "Failed to malloc cd argcs");
	while (argcs[i])
	{
		ft_parse_cd(ms, argcs[i]);
		i++;
	}
	ft_chdir(ms);
	// if (ms->pwd)
	// {
	// 	free(ms->pwd);
	// 	ms->pwd = NULL;
	// }
	// if (ms->old_pwd)
	// {
	// 	free(ms->old_pwd);
	// 	ms->old_pwd = NULL;
	// }
	if (argcs)
		ft_free_tab(argcs, -1);
}
