/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjose <mjose@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/01 14:59:49 by bsiche            #+#    #+#             */
/*   Updated: 2020/01/17 10:53:56 by alsomvil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strdup(const char *s)
{
	char	*str;
	size_t	i;

	if (!s)
		return (NULL);
	i = ft_strlen(s);
	if ((str = malloc(sizeof(char) * (i + 1))) == NULL)
		return (NULL);
	ft_memcpy(str, s, i);
	str[i++] = '\0';
	return (str);
}
