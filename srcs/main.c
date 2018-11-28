/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lterrail <lterrail@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/20 20:07:10 by lterrail          #+#    #+#             */
/*   Updated: 2018/11/28 20:21:23 by lterrail         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void		ft_copy_env(t_ms *ms, char **env)
{
	int		i;

	i = 0;
	while (env[ms->len_env])
		ms->len_env++;
	if (!(ms->env = (char **)malloc(sizeof(char *) * (ms->len_env + 1))))
		ft_exit(ms, NULL, "Failed to malloc env");
	while (i < ms->len_env)
	{
		if (!(ms->env[i] = ft_strdup(env[i])))
			ft_exit(ms, NULL, "Failed to malloc env");
		i++;
	}
	ms->env[ms->len_env] = NULL;
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
	ms->len_env = 0;
	ms->env = NULL;
	ms->pwd = NULL;
	ms->old_pwd = NULL;
	ms->first_call = 1;
	ft_copy_env(ms, env);
	return (ms);
}

static void		ft_print_prompt(t_ms *ms)
{
	int		i;

	i = 0;
	if (!(i = ft_find_env_variable(ms, "PWD=")))
		ft_printf("prompt:> ");
	else
		ft_printf(" {cyan}%s{eoc} ", ft_get_last_argc(ms->env[i]));
}

static void		ft_init_parser(t_ms *ms, char *line)
{
	char	**argcs;
	int		i;

	i = 0;
	argcs = NULL;
	if (!(argcs = ft_strsplit(line, ';')))
		ft_exit(ms, line, "Failed to malloc strplit in main");
	i = -1;
	while (argcs[++i])
		ft_parser(ms, argcs[i]);
	ft_free_tab(argcs, -1);
	free(line);
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
		ft_print_prompt(ms);
		get_next_line(0, &line);
		// {
		// 	if (g_reset_input == 1)
		// 		break ;
		// 	g_reset_input = 0;
		// }
		ft_init_parser(ms, line);
	}
	return (0);
}
