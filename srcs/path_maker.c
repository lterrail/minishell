/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_maker.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lterrail <lterrail@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/23 12:23:44 by lterrail          #+#    #+#             */
/*   Updated: 2018/11/24 14:08:52 by lterrail         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			ft_find_and_copy_paths(t_ms *ms, char **env)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!env)
		return (E_ERROR);
	while (i < ms->len_env)
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
		i++;
	}
	return (E_ERROR);
}

int			ft_search_cmd_in_paths(t_ms *ms, char *line)
{
	int		i;

	i = 0;
	while (ms->paths[i])
	{
		if (!ft_strcmp(ms->paths[i], line))
			return (E_SUCCESS);
		i++;
	}
	return (E_ERROR);
}
