/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_variable_in_env.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lterrail <lterrail@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/23 12:23:44 by lterrail          #+#    #+#             */
/*   Updated: 2018/11/26 16:17:47 by lterrail         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			ft_find_env_variable(t_ms *ms, char *var)
{
	int		i;

	i = 0;
	while (ms->env[i])
	{
		if (!ft_strncmp(ms->env[i], var, ft_strlen_char(ms->env[i], '=')))
			return (i);
		i++;
	}
	return (E_ERROR);
}

int			ft_find_and_copy_paths(t_ms *ms, char **env)
{
	int		i;
	int		j;

	i = -1;
	j = 0;
	if (ms->paths)
	{
		ft_free_tab(ms->paths, -1);
		ms->paths = NULL;
	}
	if (!env)
		return (E_ERROR);
	while (++i < ms->len_env)
	{
		if (ft_strstr(env[i], "PATH="))
		{
			while (env[i][j] != '=')
				j++;
			j++;
			if (!(ms->paths = ft_strsplit(&env[i][j], ':')))
				ft_exit(ms, NULL, "Failed to malloc ms->paths");
			return (E_SUCCESS);
		}
	}
	return (E_ERROR);
}
