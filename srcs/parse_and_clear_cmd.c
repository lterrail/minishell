/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_and_clear_cmd.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lterrail <lterrail@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/21 19:09:11 by lterrail          #+#    #+#             */
/*   Updated: 2019/01/21 19:46:02 by lterrail         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	cmd_parser_dollars_process(t_ms *ms, char **tab, int i, int j)
{
	int		ret;
	char	*tmp;

	tmp = NULL;
	ret = 0;
	if (tab[i][j] == '$')
	{
		if ((ret = ft_find_env_variable(ms->env, &tab[i][j + 1])))
		{
			if (!(tmp = ft_strndup(tab[i],
			ft_strlen_char(tab[i], '$', 0))))
				ft_exit(ms, NULL, "Failed to ft_strndup\n");
			free(tab[i]);
			if (!(tab[i] = ft_strjoin(tmp, &ms->env[ret]
				[ft_strlen_char(ms->env[ret], '=', 0) + 1])))
				ft_exit(ms, tmp, "Failed to ft_strjoin\n");
			free(tmp);
		}
	}
}

void		cmd_parser_dollars(t_ms *ms, char *line, int index)
{
	int		i;
	int		j;
	char	**tab;

	i = -1;
	tab = NULL;
	if (!(tab = ft_strsplit(line, ' ')))
		ft_exit(ms, NULL, "Failed to ft_strsplit in cmd_parser_dollars\n");
	while (tab[++i])
	{
		j = -1;
		while (tab[i][++j])
			cmd_parser_dollars_process(ms, tab, i, j);
	}
	free(ms->argcs[index]);
	if (!(ms->argcs[index] = ft_concat_params(ft_strtablen(tab), tab)))
		ft_exit(ms, NULL, "Failed to ft_concat_params in cmd_parser_dollars\n");
	ft_free_tab(tab);
}

int			cmd_parser_interpret_quot(char *s)
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

int			cmd_parser_echaper(char *s)
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
