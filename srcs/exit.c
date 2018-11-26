/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lterrail <lterrail@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/23 12:23:19 by lterrail          #+#    #+#             */
/*   Updated: 2018/11/26 16:11:14 by lterrail         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		ft_free_tab(char **tab, int len)
{
	int		i;

	i = -1;
	if (len > 0)
	{
		while (++i < len)
			free(tab[i]);
	}
	else
	{
		while (tab[++i])
			free(tab[i]);
	}
	free(tab);
}

void		ft_exit(t_ms *ms, char *str, char *msg)
{
	if (msg)
		ft_printf("{red}%s{eoc}\n", msg);
	if (str)
		free(str);
	if (ms->env)
		ft_free_tab(ms->env, ms->len_env);
	if (ms->paths)
		ft_free_tab(ms->paths, -1);
	if (ms->options)
		ft_free_tab(ms->options, -1);
	if (ms->pwd)
		free(ms->pwd);
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
