/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lterrail <lterrail@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/26 12:11:47 by lterrail          #+#    #+#             */
/*   Updated: 2018/11/29 17:55:56 by lterrail         ###   ########.fr       */
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
	if (i == 1)
		return (&str[0]);
	i--;
	while (i > 0 && str[i] != '/')
		i--;
	i++;
	return (&str[i]);
}

void		ft_get_first_argc(t_ms *ms, char *line)
{
	int		i;

	if (!(ms->first_argc = ft_strdup(line)))
		ft_exit(ms, NULL, "Failed to create ms->argc");
	i = 0;
	while (ms->first_argc[i] && ft_iscmd(ms->first_argc[i]))
		i++;
	ms->first_argc[i] = '\0';
}

char		*ft_epur_line(char *line, int len)
{
	int		i;

	i = len;
	while (line[i] && (line[i] == ' ' || line[i] == '\t'))
		i++;
	if (line[i])
		return (&line[i]);
	return (NULL);
}
