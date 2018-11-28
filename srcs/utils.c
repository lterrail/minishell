/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lterrail <lterrail@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/26 12:11:47 by lterrail          #+#    #+#             */
/*   Updated: 2018/11/28 18:21:06 by lterrail         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char		*ft_get_last_argc(char *str)
{
	int		i;

	i = 0;
	if (!ft_strcmp("PWD=/", str))
		return ("/");
	while (str[i])
		i++;
	i--;
	while (i > 1 && str[i] != '/')
		i--;
	i++;
	return (&str[i]);
}

void		ft_print_paths(t_ms *ms)
{
	int		i;

	i = -1;
	if (ft_find_and_copy_paths(ms, ms->env))
	{
		while (ms->paths[++i])
			ft_printf("%s\n", ms->paths[i]);
		ft_free_tab(ms->paths, -1);
		ms->paths = NULL;
	}
	else
		ft_printf("{red}PATH=/ Not found{eoc}\n");
}

void		ft_get_first_argc(t_ms *ms, char *line)
{
	int		i;

	if (!(ms->first_argc = ft_strdup(line)))
		ft_exit(ms, line, "Failed to create ms->argc");
	i = 0;
	while (ms->first_argc[i] && ft_iscmd(ms->first_argc[i]))
		i++;
	ms->first_argc[i] = '\0';
}

char		*ft_check_line(char *line, int len)
{
	int		i;

	i = len;
	while (line[i] && (line[i] == ' ' || line[i] == '\t'))
		i++;
	if (line[i])
		return (&line[i]);
	return (NULL);
}
