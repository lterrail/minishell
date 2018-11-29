/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lterrail <lterrail@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/28 20:13:00 by lterrail          #+#    #+#             */
/*   Updated: 2018/11/29 13:41:15 by lterrail         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void			ft_signal_handler(int sig)
{
	char	cwd[1024];

	if (sig == SIGINT)
	{
		getcwd(cwd, sizeof(cwd));
		ft_printf("\n {cyan}%s{eoc} ", ft_get_last_argc(cwd));
	}
}
