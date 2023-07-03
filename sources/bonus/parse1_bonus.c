/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrangwan <rrangwan@42abudhabi.ae>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/09 02:00:52 by rrangwan          #+#    #+#             */
/*   Updated: 2022/07/29 19:01:45 by rrangwan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D_bonus.h>

int	check_elements1(char **data, int *elem, char **map_temp)
{
	int	i;
	int	flag;

	i = 0;
	elem[8] = 0;
	flag = 0;
	while (data[elem[8]])
	{
		i = 0;
		while (data[elem[8]][i] && ft_isspace(data[elem[8]][i]))
			i++;
		if (data[elem[8]][i])
		{
			flag = check_elems3(data[elem[8]], &i, elem);
			if (flag == 1)
				return (1);
			if (flag == 0)
				return (check_elements2(data, elem, map_temp));
		}
		elem[8] += 1;
	}
	return (0);
}

int	check_elems3(char *str, int *i, int *elem)
{
	int	ctn;

	ctn = 0;
	if (check_elems1(str, i, elem, &ctn))
		return (1);
	else if (check_elems2(str, i, elem, &ctn))
		return (1);
	return (ctn);
}

int	check_elems1(char *str, int *i, int *elem, int *ctn)
{
	if (check_elems0(str, i))
	{
		if (str[*i] == 'N')
			elem[0]++;
		else if (str[*i] == 'S')
			elem[1]++;
		else if (str[*i] == 'W')
			elem[2]++;
		else if (str[*i] == 'E')
			elem[3]++;
		*i += 2;
		while (str[*i + 1] && ft_isspace(str[*i]) && str[*i] != '\n')
			*i += 1;
		if (str[*i])
			elem[7] += ft_path(str, *i);
		else
			elem[7] += 1;
		*ctn += 2;
	}
	if (elem[7] > 0)
	{
		ft_putstr_fd("Error\nTexture path failure\n", 2);
		return (1);
	}
	return (0);
}

int	check_elems0(char *str, int *i)
{
	if ((str[*i] == 'N' && str[*i + 1] && str[*i + 1] == 'O' \
				&& str[*i + 2] && ft_isspace(str[*i + 2])) \
				|| (str[*i] == 'S' && str[*i + 1] && str[*i + 1] == 'O' \
				&& str[*i + 2] && ft_isspace(str[*i + 2])) \
				|| (str[*i] == 'W' && str[*i + 1] && str[*i + 1] == 'E' \
				&& str[*i + 2] && ft_isspace(str[*i + 2])) \
				|| (str[*i] == 'E' && str[*i + 1] && str[*i + 1] == 'A' \
				&& str[*i + 2] && ft_isspace(str[*i + 2])))
		return (1);
	return (0);
}
