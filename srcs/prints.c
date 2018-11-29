/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prints.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lterrail <lterrail@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/29 17:54:43 by lterrail          #+#    #+#             */
/*   Updated: 2018/11/29 17:55:17 by lterrail         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		ft_print_paths(t_ms *ms)
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

void		ft_print_env(t_ms *ms)
{
	int		i;

	i = 0;
	if (!ms->env)
	{
		ft_printf("{red}No variable in env{eoc}\n");
		return ;
	}
	while (i < ms->len_env)
	{
		ft_printf("%s\n", ms->env[i]);
		i++;
	}
	if (i == 0)
		ft_printf("{red}No variable in env{eoc}\n");
}

void		ft_print_prompt(void)
{
	char	cwd[1024];

	getcwd(cwd, sizeof(cwd));
	ft_printf(" {cyan}%s{eoc} ", ft_get_last_argc(cwd));
}
