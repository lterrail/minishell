/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prints.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lterrail <lterrail@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/29 17:54:43 by lterrail          #+#    #+#             */
/*   Updated: 2018/12/01 16:32:54 by lterrail         ###   ########.fr       */
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
		ft_free_tab(ms->paths);
		ms->paths = NULL;
	}
	else
		ft_printf("{red}PATH=/ Not found{eoc}\n");
}

void		ft_print_env(char **env)
{
	int		i;

	i = 0;
	if (!env || !env[0])
	{
		ft_printf("{red}No variable in env{eoc}\n");
		return ;
	}
	while (env[i])
	{
		ft_printf("%s\n", env[i]);
		i++;
	}
}

void		ft_print_prompt(void)
{
	char	cwd[1024];

	if (!getcwd(cwd, sizeof(cwd)))
		ft_printf("\n :> ");
	else
		ft_printf(" {cyan}%s{eoc} ", ft_get_last_argc(cwd));
}
