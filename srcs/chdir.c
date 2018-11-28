/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chdir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lterrail <lterrail@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/28 19:21:41 by lterrail          #+#    #+#             */
/*   Updated: 2018/11/28 19:22:04 by lterrail         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		ft_chdir_back(t_ms *ms, char *line)
{
	int		i;

	i = ft_find_env_variable(ms, "PWD=");
	if (access(line, F_OK) != 0)
	{
		ms->first_call = 1;
		ft_printf("{red}cd: no such file or directory: %s{eoc}\n", line);
	}
	else if (access(line, X_OK) != 0)
	{
		ms->first_call = 1;
		ft_printf("{red}cd: permission denied: %s{eoc}\n", line);
	}
	else if (!chdir(line))
	{
		free(ms->env[i]);
		if (!(ms->env[i] = ft_strjoin("PWD=", ms->pwd)))
			ft_exit(ms, line, "Failed to malloc");
	}
}

void		ft_chdir(t_ms *ms, char *line)
{
	int		i;
	char	cwd[1024];

	i = ft_find_env_variable(ms, "PWD=");
	if (!(ms->old_pwd = ft_strdup(&ms->env[i][4])))
		ft_exit(ms, line, "Failed to malloc");
	if (access(line, F_OK) != 0)
	{
		ms->first_call = 1;
		ft_printf("{red}cd: no such file or directory: %s{eoc}\n", line);
	}
	else if (access(line, X_OK) != 0)
	{
		ms->first_call = 1;
		ft_printf("{red}cd: permission denied: %s{eoc}\n", line);
	}
	else if (!chdir(line))
	{
		if (!(ms->pwd = ft_strdup(getcwd(cwd, sizeof(cwd)))))
			ft_exit(ms, line, "Failed to malloc");
		free(ms->env[i]);
		if (!(ms->env[i] = ft_strjoin("PWD=", ms->pwd)))
			ft_exit(ms, line, "Failed to malloc");
	}
}
