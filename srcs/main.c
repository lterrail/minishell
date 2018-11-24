/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lterrail <lterrail@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/20 20:07:10 by lterrail          #+#    #+#             */
/*   Updated: 2018/11/24 11:50:49 by lterrail         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void		ft_copy_env(t_ms *ms, char **env)
{
	int		i;

	i = 0;
	while (env[ms->len_env])
		ms->len_env++;
	if (!(ms->env = (char **)malloc(sizeof(char *) * ms->len_env)))
		ft_exit(ms, NULL, "Failed to malloc env");
	while (i < ms->len_env)
	{
		if (!(ms->env[i] = ft_strdup(env[i])))
			ft_exit(ms, NULL, "Failed to malloc env");
		i++;
	}
}

static t_ms		*ft_init_ms(t_ms *ms, char **env)
{
	ms = (t_ms *)malloc(sizeof(t_ms));
	if (!ms)
		ft_exit(NULL, NULL, "Failed to malloc structure ms");
	ms->paths = NULL;
	ms->len_env = 0;
	ms->first_argc = NULL;
	ms->options = NULL;
	if (!(ms->pwd = ft_strdup("Minishell")))
		ft_exit(ms, NULL, "Failed to malloc ms->pwd");
	ft_copy_env(ms, env);
	return (ms);
}

int				main(int ac, char **av, char **env)
{
	(void)ac;
	(void)av;
	char	*line;
	t_ms	*ms;

	ms = NULL;
	line = NULL;
	ms = ft_init_ms(ms, env);
	while (1)
	{
		ft_printf("{cyan} %s{eoc} ", ms->pwd);
		get_next_line(0, &line);
		ft_parse_cmd(ms, line);
		free(line);
	}
	return (0);
}
