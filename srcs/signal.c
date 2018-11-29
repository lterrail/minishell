/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lterrail <lterrail@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/28 20:13:00 by lterrail          #+#    #+#             */
/*   Updated: 2018/11/29 17:26:07 by lterrail         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void			ft_signal_handler(int sig)
{
	char	cwd[1024];
	char	*tmp;

	tmp = NULL;
	if (sig == SIGINT)
	{
		tmp = ft_get_last_argc(getcwd(cwd, sizeof(cwd)));
		if (g_reset_input == 0)
			ft_printf("\n {cyan}%s{eoc} ", tmp);
		else
			ft_printf("\n");
	}
}
