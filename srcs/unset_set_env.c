/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_set_env.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lterrail <lterrail@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/23 14:27:44 by lterrail          #+#    #+#             */
/*   Updated: 2018/11/24 16:59:38 by lterrail         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		ft_print_env(t_ms *ms)
{
	int		i;

	i = 0;
	while (i < ms->len_env)
	{
		ft_printf("%s\n", ms->env[i]);
		i++;
	}
}

static void	ft_realloc_msenv(t_ms *ms, char *line)
{
	int		i;
	char	**new;

	i = 0;
	new = NULL;
	if (!(new = (char **)malloc(sizeof(char *) * (ms->len_env + 1))))
		ft_exit(ms, NULL, "Failed to realloc ms->env");
	while (i < ms->len_env)
	{
		if (line && i + 1 == ms->len_env)
		{
			if (!(new[i] = ft_strdup(line)))
				ft_exit(ms, NULL, "Failed to add setenv");
			i++;
		}
		else
		{
			new[i] = ms->env[i];
			i++;
		}
	}
	free(ms->env);
	ms->env = new;
	ms->env[ms->len_env] = NULL;
}

int			ft_setenv(t_ms *ms, char *line)
{
	int		i;

	i = 0;
	while (i < ms->len_env)
	{
		if (!ft_strncmp(ms->env[i], line, ft_strlen_char(ms->env[i], '=')))
		{
			ft_printf("%s already exist\n", line);
			ft_printf(" {red}[old] -> %s\n", ms->env[i]);
			free(ms->env[i]);
			if (!(ms->env[i] = ft_strdup(line)))
				ft_exit(ms, NULL, "Failed to add new variable in env");
			ft_printf("{green} [new] -> %s{eoc}\n", line);
			return (E_SUCCESS);
		}
		i++;
	}
	ms->len_env++;
	ft_printf("{green}Add: %s{eoc}\n", line);
	ft_realloc_msenv(ms, line);
	return (E_SUCCESS);
}

int			ft_unsetenv(t_ms *ms, char *line)
{
	int		i;

	i = 0;
	if (ft_strlen(&line[i]) < 1)
		return (E_ERROR);
	while (i < ms->len_env)
	{
		if (line && !ft_strncmp(ms->env[i], line, ft_strlen_char(ms->env[i], '=')))
		{
			ft_printf("{red}Deleted: %s{eoc}\n", ms->env[i]);
			free(ms->env[i]);
			while (i + 1 < ms->len_env)
			{
				if (!(ms->env[i] = ft_strdup(ms->env[i + 1])))
					ft_exit(ms, NULL, "Failed to realloc each env line");
				free(ms->env[i + 1]);
				i++;
			}
			ms->len_env--;
			ft_realloc_msenv(ms, NULL);
			return (E_SUCCESS);
		}
		i++;
	}
	ft_printf("{red}Unsetenv %s not found{eoc}\n", line);
	return (E_ERROR);
}
