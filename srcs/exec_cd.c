/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lterrail <lterrail@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/24 17:02:03 by lterrail          #+#    #+#             */
/*   Updated: 2018/11/28 19:26:52 by lterrail         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void		ft_add_oldpwd_in_env(t_ms *ms, char *line)
{
	char	*tmp;

	tmp = NULL;
	if (!(tmp = ft_strjoin("OLDPWD=", ms->old_pwd)))
		ft_exit(ms, line, "Failed to malloc in ft_add_oldpwd");
	ft_setenv(ms, tmp, 1);
	free(tmp);
}

static int		ft_check_tild(t_ms *ms, char *line)
{
	int		i;

	i = 0;
	if (!line || (line && line[0] == '~'))
	{
		if (!(i = ft_find_env_variable(ms, "HOME=")))
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

static int		ft_solve_simple_case(t_ms *ms, char *line)
{
	int		i;
	char	*tmp;

	i = 0;
	if (!(i = ft_check_tild(ms, line)))
		return (E_ERROR);
	if (!line)
	{
		ft_chdir(ms, &ms->env[i][5]);
		return (E_ERROR);
	}
	else if (line && line[0] == '~')
	{
		if (!(tmp = ft_strjoin(&ms->env[i][5], &line[1])))
			ft_exit(ms, line, "Failed to malloc in ft_solve_simple_case");
		ft_chdir(ms, tmp);
		free(tmp);
		return (E_ERROR);
	}
	if (!ft_strcmp(line, "-") && ms->first_call == 1)
		return (E_ERROR);
	else if (!ft_strcmp(line, "-") && ms->first_call == 0)
		return (E_SUCCESS);
	ms->first_call = 0;
	return (E_SUCCESS);
}

void			ft_init_cd(t_ms *ms, char *line)
{
	int		i;
	char	*tmp;

	tmp = NULL;
	i = -1;
	if (!ft_find_env_variable(ms, "PWD="))
	{
		ft_printf("{red}Variable in env PWD= doesn't exist{eoc}\n");
		return ;
	}
	if (line && line[0] != '-')
		ft_free_cd(ms);
	if (!ft_solve_simple_case(ms, line))
		return ;
	if (!ft_strcmp(line, "-"))
	{
		tmp = ms->old_pwd;
		ms->old_pwd = ms->pwd;
		ms->pwd = tmp;
		ft_chdir_back(ms, ms->pwd);
	}
	else
		ft_chdir(ms, line);
	ft_add_oldpwd_in_env(ms, line);
}
