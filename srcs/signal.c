/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lterrail <lterrail@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/28 20:13:00 by lterrail          #+#    #+#             */
/*   Updated: 2018/11/29 19:15:43 by lterrail         ###   ########.fr       */
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
		if (!getcwd(cwd, sizeof(cwd)))
			ft_printf("\n :> ");
		else
		{
			if (g_reset_input == 0)
				ft_printf("\n {cyan}%s{eoc} ", ft_get_last_argc(cwd));
			else
				ft_printf("\n");
		}
	}
}
