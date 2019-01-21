/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lterrail <lterrail@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/21 16:11:19 by lterrail          #+#    #+#             */
/*   Updated: 2019/01/21 16:21:06 by lterrail         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		ft_echo(t_ms *ms, char *line)
{
	int		i_var;
	int		i;
	char	**tab;

	i = 0;
	i_var = 0;
	tab = NULL;
	if (!(tab = ft_strsplit(&line[4], ' ')))
		ft_exit(ms, NULL, "Failed to malloc ft_strsplit in ft_echo\n");
	while (tab[i])
	{
		if (ft_strchr(tab[i], '~') && (i_var = ft_find_env_variable(ms->env,
			"HOME=")))
			ft_printf("%s", &ms->env[i_var][5]);
		else
			ft_printf("%s", tab[i]);
		i++;
		if (i < ft_strtablen(tab))
			ft_printf(" ");
	}
	ft_printf("\n");
	ft_free_tab(tab);
}
