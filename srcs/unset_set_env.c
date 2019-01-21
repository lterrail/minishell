/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_set_env.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lterrail <lterrail@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/23 14:27:44 by lterrail          #+#    #+#             */
/*   Updated: 2019/01/21 15:29:14 by lterrail         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**ft_realloc_msenv(t_ms *ms, char *line, int len_env, char **env)
{
	int		i;
	char	**new;

	i = 0;
	new = NULL;
	if (!(new = (char **)malloc(sizeof(char *) * (len_env + 1))))
		ft_exit(ms, NULL, "Failed to realloc ms->env");
	while (i < len_env)
	{
		if (line && i + 1 == len_env)
		{
			if (!(new[i] = ft_strdup(line)))
				ft_exit(ms, NULL, "Failed to add setenv");
			i++;
		}
		else
		{
			new[i] = env[i];
			i++;
		}
	}
	free(env);
	new[i] = NULL;
	return (new);
}

static int	ft_is_line(char *line, char *str)
{
	if (!line)
	{
		ft_printf("{red}usage: %s [variable]{eoc}\n", str);
		return (E_ERROR);
	}
	return (E_SUCCESS);
}

char		**ft_setenv(t_ms *ms, char *line, int flag, char **env)
{
	int		i;

	i = -1;
	if (!ft_is_line(line, "setenv"))
		return (E_ERROR);
	while (env[++i])
	{
		if (!ft_strncmp(line, env[i], ft_strlen_char(env[i], '=',
		ft_strlen_char(line, '=', 0))))
		{
			!flag ? ft_printf("%s already exist\n", line) : 0;
			!flag ? ft_printf(" {red}[old] -> %s\n", env[i]) : 0;
			free(env[i]);
			if (!(env[i] = ft_strdup(line)))
				ft_exit(ms, NULL, "Failed to add new variable in env");
			!flag ? ft_printf("{green} [new] -> %s{eoc}\n", line) : 0;
			return (env);
		}
	}
	!flag ? ft_printf("{green}Add: %s{eoc}\n", line) : 0;
	env = ft_realloc_msenv(ms, line, ft_strtablen(env) + 1, env);
	return (env);
}

char		**ft_unsetenv(t_ms *ms, char *line, char **env)
{
	int		i;

	i = -1;
	if (!ft_is_line(line, "unsetenv"))
		return (E_ERROR);
	while (env[++i])
	{
		if (!ft_strncmp(line, env[i], ft_strlen_char(env[i], '=',
		ft_strlen(line))))
		{
			ft_printf("{red}Deleted: %s{eoc}\n", env[i]);
			free(env[i]);
			while (env[i + 1])
			{
				if (!(env[i] = ft_strdup(env[i + 1])))
					ft_exit(ms, NULL, "Failed to realloc each env line");
				free(env[i + 1]);
				i++;
			}
			env = ft_realloc_msenv(ms, NULL, ft_strtablen(env) - 1, env);
			return (env);
		}
	}
	ft_printf("{red}Unsetenv %s not found{eoc}\n", line);
	return (env);
}
