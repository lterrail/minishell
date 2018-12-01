/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtabdup.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lterrail <lterrail@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/01 15:34:34 by lterrail          #+#    #+#             */
/*   Updated: 2018/12/01 15:39:06 by lterrail         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		**ft_strtabdup(char **tab)
{
	char	**dup;
	char	**ddup;

	if (!tab)
		return (NULL);
	if (!(dup = (char **)malloc(sizeof(char *) * (ft_strtablen(tab) + 1))))
		return (NULL);
	ddup = dup;
	while (*tab)
		if (!(*(ddup++) = ft_strdup(*(tab++))))
			return (NULL);
	*ddup = NULL;
	return (dup);
}
