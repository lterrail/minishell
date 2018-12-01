/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_builtin.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lterrail <lterrail@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/28 18:18:08 by lterrail          #+#    #+#             */
/*   Updated: 2018/12/01 16:28:08 by lterrail         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char		*ft_search_valid_builtin(t_ms *ms)
{
	int		i;
	char	*path;
	char	*tmp;

	i = -1;
	if (!(tmp = ft_strjoin("/", ms->first_argc)))
		ft_exit(ms, NULL, "Failed to malloc in ft_check_access");
	if (ft_find_and_copy_paths(ms, ms->env))
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
