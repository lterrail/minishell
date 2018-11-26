/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cd_functions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lterrail <lterrail@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/26 19:41:03 by lterrail          #+#    #+#             */
/*   Updated: 2018/11/26 19:52:06 by lterrail         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		ft_del_last_argc(t_ms *ms)
{
	int		i;

	i = 0;
	while (ms->pwd[i])
		i++;
	i--;
	while (i > 1 && ms->pwd[i] != '/')
		i--;
	ms->pwd[i] = '\0';
}

void		ft_add_argc(t_ms *ms, char *argcs)
{
	char	*tmp;

	tmp = NULL;
	if (!(tmp = ft_strjoin(ms->pwd, "/")))
		ft_exit(ms, NULL, "Failed to malloc");
	if (!(ms->pwd = ft_strjoin(tmp, argcs)))
		ft_exit(ms, tmp, "Failed to malloc");
}

void		ft_swap_argcs(t_ms *ms)
{
	char	*tmp;

	tmp = NULL;
	tmp = ms->old_pwd;
	ms->old_pwd = ms->pwd;
	ms->pwd = tmp;
}

void		ft_get_home(t_ms *ms)
{
	int		i;
	char	*tmp;

	i = 0;
	tmp = NULL;
	if (!(i = ft_find_env_variable(ms, "HOME=")))
	{
		ft_printf("{red}%sNo variable HOME= in env{eoc}\n");
		ms->error = 1;
		return ;
	}
	tmp = ms->env[i];
	ms->pwd = &tmp[5];
}
