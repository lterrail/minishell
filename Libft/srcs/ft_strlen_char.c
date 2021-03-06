/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen_char.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lterrail <lterrail@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/24 16:49:11 by lterrail          #+#    #+#             */
/*   Updated: 2019/01/21 15:08:03 by lterrail         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_strlen_char(char *str, char c, int len)
{
	int		i;

	i = -1;
	while (str[++i])
	{
		if (str[i] == c)
		{
			if (len > i)
				return (len);
			return (i);
		}
	}
	if (len > i)
		return (len);
	return (i);
}
