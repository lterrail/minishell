/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lterrail <lterrail@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/01 12:06:49 by lterrail          #+#    #+#             */
/*   Updated: 2019/01/17 16:20:17 by lterrail         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char		**ft_delete_env(t_ms *ms, char **env)
{
	ft_free_tab(env);
	if (!(env = (char **)malloc(sizeof(char *) * 1)))
		ft_exit(ms, NULL, "Failed to malloc env");
	env[0] = NULL;
	return (env);
}

static char	**ft_refresh_variable_shlvl(t_ms *ms, char **env)
{
	int		i;
	char	*tmp;
	char	*tmp2;
	int		j;

	tmp = NULL;
	tmp2 = NULL;
	i = 0;
	j = 0;
	if ((j = ft_find_env_variable(env, "SHLVL=")))
	{
		while (env[j][i + 1])
			i++;
		if (!(tmp2 = ft_strdup(&env[j][i])))
			ft_exit(ms, NULL, "Failed to malloc strdup");
		tmp2[0] += 1;
		if (!(tmp = ft_strjoin("SHLVL=", tmp2)))
			ft_exit(ms, NULL, "Failed to malloc strjoin");
		env = ft_setenv(ms, tmp, 1, env);
		free(tmp2);
		free(tmp);
	}
	else
		return (env);
	return (env);
}

static char	**ft_exec_cmd_in_env(t_ms *ms, char **env_tmp, char **argcs, int i)
{
	char	*path;
	char	*test;

	path = NULL;
	test = NULL;
	if (!ft_strncmp(argcs[i], "minishell", ft_strlen("minishell")))
	{
		env_tmp = ft_refresh_variable_shlvl(ms, env_tmp);
		ft_exec_cmd(ms, argcs[i], argcs[i], env_tmp);
		return (env_tmp);
	}
	if (!(path = ft_search_valid_builtin(ms, argcs[i], env_tmp)))
	{
		ft_printf("{red}No such file or directory: %s{eoc}\n", argcs[i]);
		free(path);
		return (env_tmp);
	}
	if (!(test = ft_concat_params(ft_strtablen(&argcs[i]), &argcs[i])))
		ft_exit(ms, NULL, "Failed to malloc in ft_concat_params");
	ft_exec_cmd_with_path(ms, path, test, env_tmp);
	free(path);
	return (env_tmp);
}

static char	**ft_exec_env(t_ms *ms, char **env, char **env_tmp, char **argcs)
{
	int		i;

	i = -1;
	while (argcs[++i])
	{
		if (!ft_strcmp(argcs[0], "-i") && !argcs[1])
		{
			ms->env = ft_delete_env(ms, env);
			return (env_tmp);
		}
		else if (!ft_strcmp(argcs[i], "-i"))
			env_tmp = ft_delete_env(ms, env_tmp);
		else if (ft_is_variable(argcs[i]))
			env_tmp = ft_setenv(ms, argcs[i], 1, env_tmp);
		else if (ft_exec_cmd_in_env(ms, env_tmp, argcs, i))
			return (env_tmp);
	}
	ft_print_env(env_tmp);
	return (env_tmp);
}

void		ft_parse_env(t_ms *ms, char *line, char **env)
{
	char	**env_tmp;
	char	**argcs;

	argcs = NULL;
	if (!line)
	{
		ft_print_env(env);
		return ;
	}
	if (!(env_tmp = ft_strtabdup(env)))
		ft_exit(ms, NULL, "Failed to malloc strtabdup in ft_parse_env");
	if (!(argcs = ft_strsplit(line, ' ')))
		ft_exit(ms, NULL, "Failed to malloc strsplit in ft_parse_env");
	env_tmp = ft_exec_env(ms, env, env_tmp, argcs);
	if (argcs)
		ft_free_tab(argcs);
	if (env_tmp)
		ft_free_tab(env_tmp);
}
