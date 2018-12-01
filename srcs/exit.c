/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lterrail <lterrail@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/23 12:23:19 by lterrail          #+#    #+#             */
/*   Updated: 2018/12/01 13:11:08 by lterrail         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		ft_free_cd(t_ms *ms)
{
	if (ms->pwd)
	{
		free(ms->pwd);
		ms->pwd = NULL;
	}
	if (ms->old_pwd)
	{
		free(ms->old_pwd);
		ms->old_pwd = NULL;
	}
}

void		ft_free_tab(char **tab)
{
	int		i;

	i = -1;
	while (tab[++i])
		free(tab[i]);
	free(tab);
	tab = NULL;
}

void		ft_exit(t_ms *ms, char *str, char *msg)
{
	if (msg)
		ft_printf("{red}%s{eoc}\n", msg);
	if (str)
		free(str);
	if (ms->env)
		ft_free_tab(ms->env);
	if (ms->paths)
		ft_free_tab(ms->paths);
	if (ms->options)
		ft_free_tab(ms->options);
	if (ms->argcs)
		ft_free_tab(ms->argcs);
	if (ms->first_argc)
		free(ms->first_argc);
	if (ms->old_pwd)
		free(ms->old_pwd);
	if (ms->pwd)
		free(ms->pwd);
	if (ms)
		free(ms);
	exit(0);
}
