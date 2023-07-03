/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkintana <gkintana@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/26 19:12:11 by gkintana          #+#    #+#             */
/*   Updated: 2022/07/02 14:03:18 by gkintana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

char	*ft_strdup(const char *s1)
{
	char	*dup;

	dup = (char *)ft_calloc((ft_strlen(s1) + 1), sizeof(char));
	if (!dup)
		return (NULL);
	ft_memcpy(dup, s1, ft_strlen(s1));
	return (dup);
}
