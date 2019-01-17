/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_builtin.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lterrail <lterrail@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/28 18:18:08 by lterrail          #+#    #+#             */
/*   Updated: 2019/01/14 14:30:37 by lterrail         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char		*ft_search_valid_builtin(t_ms *ms, char *cmd, char **env)
{
	int		i;
	char	*path;
	char	*tmp;

	i = -1;
	if (!(tmp = ft_strjoin("/", cmd)))
		ft_exit(ms, NULL, "Failed to malloc in ft_check_access");
	if (ft_find_and_copy_paths(ms, env))
	{
		while (ms->paths[++i])
		{
			if (!(path = ft_strjoin(ms->paths[i], tmp)))
				ft_exit(ms, tmp, "Failed to malloc in ft_check_access");
			if ((access(path, F_OK)) == 0 && access(path, X_OK) == 0)
			{
				free(tmp);
				return (path);
			}
			free(path);
		}
	}
	free(tmp);
	return (NULL);
}
