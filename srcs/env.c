/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lterrail <lterrail@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/01 12:06:49 by lterrail          #+#    #+#             */
/*   Updated: 2018/12/01 14:55:13 by lterrail         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**ft_strtabdup(char **tab)
{
	char	**dup;
	char	**ddup;

	if (!tab)
		return (NULL);
	if (!(dup = (char **)ft_memalloc(sizeof(char *) * (ft_get_tablen(tab) + 1))))
		return (NULL);
	ddup = dup;
	while (*tab)
		if (!(*(ddup++) = ft_strdup(*(tab++))))
			return (NULL);
	*ddup = NULL;
	return (dup);
}

char		**ft_delete_env(t_ms *ms, char **env)
{
	ft_free_tab(env);
	if (!(env = (char **)malloc(sizeof(char *) * 1)))
		ft_exit(ms, NULL, "Failed to malloc env");
	env[0] = NULL;
	return (env);
}

static int	ft_is_variable(char *str)
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

void		ft_parse_env(t_ms *ms, char *line, char **env)
{
	char	**env_tmp;
	char	**argcs;
	int		ret;
	int		i;

	i = 0;
	argcs = NULL;
	ret = 0;
	if (!line)
	{
		ft_print_env(env);
		return ;
	}
	env_tmp = ft_strtabdup(env);
	if (!(argcs = ft_strsplit(line, ' ')))
		ft_exit(ms, NULL, "Failed to malloc strsplit in ft_parse_env");
	while (argcs[i])
	{
		if (!ft_strcmp(argcs[0], "-i"))
			env_tmp = ft_delete_env(ms, env);
		else if (ft_is_variable(argcs[i]))
			env_tmp = ft_setenv(ms, argcs[i], 0, env_tmp);
		else if (!ft_strcmp(argcs[i], "minishell"))
		{
			ft_exec_cmd_with_path(ms, argcs[i], argcs[i], env_tmp);
			break ;
		}
		i++;
	}
	ft_print_env(env_tmp);
	if (argcs)
		ft_free_tab(argcs);
}
