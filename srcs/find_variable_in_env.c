/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_variable_in_env.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lterrail <lterrail@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/23 12:23:44 by lterrail          #+#    #+#             */
/*   Updated: 2019/01/21 15:25:57 by lterrail         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			ft_is_variable(char *str)
{
	int		i;

	i = -1;
	while (str[++i])
	{
		if (str[i] == '=' && i != 0)
			return (E_SUCCESS);
	}
	return (E_ERROR);
}

int			ft_find_env_variable(char **env, char *var)
{
	int		i;

	i = 0;
	while (env[i])
	{
		if (!ft_strncmp(env[i], var, ft_strlen_char(env[i], '=',
		ft_strlen(var))))
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
		ft_free_tab(ms->paths);
		ms->paths = NULL;
	}
	if (!env)
		return (E_ERROR);
	while (env[++i])
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
