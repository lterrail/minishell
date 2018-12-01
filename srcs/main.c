/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lterrail <lterrail@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/20 20:07:10 by lterrail          #+#    #+#             */
/*   Updated: 2018/12/01 13:45:17 by lterrail         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void		ft_copy_env(t_ms *ms, char **env)
{
	int		i;
	int		len_env;

	i = 0;
	len_env = 0;
	while (env[len_env])
		len_env++;
	if (!(ms->env = (char **)malloc(sizeof(char *) * (len_env + 1))))
		ft_exit(ms, NULL, "Failed to malloc env");
	while (i < len_env)
	{
		if (!(ms->env[i] = ft_strdup(env[i])))
			ft_exit(ms, NULL, "Failed to malloc env");
		i++;
	}
	ms->env[i] = NULL;
}

static t_ms		*ft_init_ms(t_ms *ms, char **env)
{
	ms = (t_ms *)malloc(sizeof(t_ms));
	if (!ms)
		ft_exit(NULL, NULL, "Failed to malloc structure ms");
	ms->paths = NULL;
	ms->first_argc = NULL;
	ms->options = NULL;
	ms->env = NULL;
	ms->pwd = NULL;
	ms->old_pwd = NULL;
	ms->first_call = 1;
	ms->argcs = NULL;
	ft_copy_env(ms, env);
	return (ms);
}

static void		ft_init_parser(t_ms *ms, char *line)
{
	int		i;

	i = -1;
	if (!(ms->argcs = ft_strsplit(line, ';')))
		ft_exit(ms, line, "Failed to malloc strplit in main");
	free(line);
	while (ms->argcs[++i])
		ft_parser(ms, ms->argcs[i]);
	ft_free_tab(ms->argcs);
}

int				main(int ac, char **av, char **env)
{
	char	*line;
	t_ms	*ms;

	(void)ac;
	(void)av;
	ms = NULL;
	ms = ft_init_ms(ms, env);
	g_reset_input = 0;
	signal(SIGINT, ft_signal_handler);
	while (1)
	{
		ft_print_prompt();
		get_next_line(0, &line);
		if (line)
			ft_init_parser(ms, line);
		else
			ft_printf("\n");
	}
	return (0);
}
