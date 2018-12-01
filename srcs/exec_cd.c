/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lterrail <lterrail@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/24 17:02:03 by lterrail          #+#    #+#             */
/*   Updated: 2018/12/01 18:03:15 by lterrail         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void		ft_add_oldpwd_in_env(t_ms *ms)
{
	char	*tmp;

	tmp = NULL;
	if (!(tmp = ft_strjoin("OLDPWD=", ms->old_pwd)))
		ft_exit(ms, NULL, "Failed to malloc in ft_add_oldpwd");
	ft_setenv(ms, tmp, 1, ms->env);
	free(tmp);
}

static int		ft_check_tild(t_ms *ms, char *line)
{
	int		i;

	i = 0;
	if (!line || (line && line[0] == '~'))
	{
		if (!(i = ft_find_env_variable(ms->env, "HOME=")))
		{
			ft_printf("{red}Variable in env HOME= doesn't exist{eoc}\n");
			return (E_ERROR);
		}
		else
			return (i);
	}
	else
		return (E_SUCCESS);
}

static int		ft_solve_simple_case(t_ms *ms, char *line, int i)
{
	char	*tmp;
	int		home;

	if (!(home = ft_check_tild(ms, line)))
		return (E_ERROR);
	if (!line)
	{
		ft_chdir(ms, &ms->env[home][5], i);
		ft_add_oldpwd_in_env(ms);
		return (E_ERROR);
	}
	else if (line[0] == '~')
	{
		if (!(tmp = ft_strjoin(&ms->env[home][5], &line[1])))
			ft_exit(ms, NULL, "Failed to malloc in ft_solve_simple_case");
		ft_chdir(ms, tmp, i);
		ft_add_oldpwd_in_env(ms);
		free(tmp);
		return (E_ERROR);
	}
	if (!ft_strcmp(line, "-") && ms->first_call == 1)
		return (E_ERROR);
	else if (!ft_strcmp(line, "-") && ms->first_call == 0)
		return (E_SUCCESS);
	return (E_SUCCESS);
}

void			ft_init_cd(t_ms *ms, char *line)
{
	int		i;
	char	*tmp;

	tmp = NULL;
	i = 0;
	if (!(i = ft_find_env_variable(ms->env, "PWD=")))
	{
		ft_printf("{red}Variable in env PWD= doesn't exist{eoc}\n");
		return ;
	}
	if (!line || (line && line[0] != '-'))
		ft_free_cd(ms);
	if (!ft_solve_simple_case(ms, line, i))
		return ;
	if (!ft_strcmp(line, "-"))
	{
		tmp = ms->old_pwd;
		ms->old_pwd = ms->pwd;
		ms->pwd = tmp;
		ft_chdir_back(ms, ms->pwd, i);
	}
	else
		ft_chdir(ms, line, i);
	ft_add_oldpwd_in_env(ms);
}
