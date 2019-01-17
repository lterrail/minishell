/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_concat_params.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lterrail <lterrail@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/17 15:37:55 by lterrail          #+#    #+#             */
/*   Updated: 2019/01/17 15:38:49 by lterrail         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_concat_params(int argc, char **argv)
{
	char	*args;
	int		i;
	int		j;
	int		k;
	int		mem;

	mem = 0;
	i = -1;
	while (++i < argc)
		mem += ft_strlen(argv[i]) + 1;
	if (!(args = (char*)malloc(sizeof(char) * mem)))
		return (NULL);
	i = -1;
	k = -1;
	while (++i < argc)
	{
		j = 0;
		while (argv[i][j] != '\0')
			args[++k] = argv[i][j++];
		args[++k] = i == argc - 1 ? '\0' : ' ';
	}
	return (args);
}
