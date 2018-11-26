/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lterrail <lterrail@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/26 12:11:47 by lterrail          #+#    #+#             */
/*   Updated: 2018/11/26 19:15:34 by lterrail         ###   ########.fr       */
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
