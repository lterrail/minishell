/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lterrail <lterrail@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/26 12:11:47 by lterrail          #+#    #+#             */
/*   Updated: 2019/01/17 15:59:01 by lterrail         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int				cmd_parser_interpret_quot(char *s)
{
	int		diff;
	int		i;

	i = 0;
	diff = 0;
	while (s[i + diff])
	{
		while (s[i + diff] == '"' && (!(i + diff) || s[i + diff - 1] != '\\'))
			diff++;
		s[i] = s[i + diff];
		if (s[i + diff])
			i++;
	}
	s[i] = '\0';
	return (EXIT_SUCCESS);
}

int				cmd_parser_echaper(char *s)
{
	int		diff;
	int		i;

	i = 0;
	diff = 0;
	while (s[i + diff])
	{
		if (s[i + diff] == '\\' && s[i + diff + 1] == '"')
			diff++;
		s[i] = s[i + diff];
		i++;
	}
	s[i] = '\0';
	return (EXIT_SUCCESS);
}

char			*ft_get_last_argc(char *str)
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

void			ft_get_first_argc(t_ms *ms, char *line)
{
	int		i;

	if (!(ms->first_argc = ft_strdup(line)))
		ft_exit(ms, NULL, "Failed to create ms->argc");
	i = 0;
	while (ms->first_argc[i] && ms->first_argc[i] != ' ')
		i++;
	ms->first_argc[i] = '\0';
}

char			*ft_epur_line(char *line, int len)
{
	int		i;

	i = len;
	while (line[i] && (line[i] == ' ' || line[i] == '\t'))
		i++;
	if (line[i])
		return (&line[i]);
	return (NULL);
}
