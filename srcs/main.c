/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lterrail <lterrail@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/20 20:07:10 by lterrail          #+#    #+#             */
/*   Updated: 2018/11/29 14:31:26 by lterrail         ###   ########.fr       */
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
	ms->argcs = NULL;
	ft_copy_env(ms, env);
	return (ms);
}

static void		ft_print_prompt(void)
{
	char	cwd[1024];

	getcwd(cwd, sizeof(cwd));
	ft_printf(" {cyan}%s{eoc} ", ft_get_last_argc(cwd));
}

static void		ft_init_parser(t_ms *ms, char *line)
{
	int		i;

	i = 0;
	if (!(ms->argcs = ft_strsplit(line, ';')))
		ft_exit(ms, line, "Failed to malloc strplit in main");
	free(line);
	i = -1;
	while (ms->argcs[++i])
		ft_parser(ms, ms->argcs[i]);
	ft_free_tab(ms->argcs, -1);
	ms->argcs = NULL;
}

int				main(int ac, char **av, char **env)
{
	char	*line;
	t_ms	*ms;

	(void)ac;
	(void)av;
	ms = NULL;
	ms = ft_init_ms(ms, env);
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
