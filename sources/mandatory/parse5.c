/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse5.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrangwan <rrangwan@42abudhabi.ae>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/09 02:00:52 by rrangwan          #+#    #+#             */
/*   Updated: 2022/07/29 19:02:05 by rrangwan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>

int	check_left(char **map)
{
	int	j;

	j = check_last(map) - 1;
	while (j > 0)
	{
		if (check_left1(map, &j))
			return (1);
		j -= 1;
	}
	return (0);
}

int	check_left1(char **map, int *j)
{
	int	flag[2];
	int	i;

	ft_bzero(&flag, sizeof(int) * 2);
	i = 0;
	while (map[*j][i] && map[*j][i] == ' ')
	{
		i++;
		if (map[*j][i] && map[*j][i] == '0')
			return (1);
	}
	if (map[*j][i] && map[*j][i] != '1')
		return (1);
	while (map[*j][i] && map[*j][i] == '1')
	{
		if (map[*j + 1][i] && map[*j + 1][i] == '1')
			flag[0] = 1;
		if (map[*j - 1][i] && map[*j - 1][i] == '1')
			flag[1] = 1;
		i++;
	}
	if (flag[0] == 0 || flag[1] == 0)
		return (1);
	return (0);
}

int	check_right(char **map)
{
	int	j;

	j = check_last(map) - 1;
	while (j > 0)
	{
		if (check_right1(map, &j))
			return (1);
		j -= 1;
	}
	return (0);
}

int	check_right1(char **map, int *j)
{
	int	flag[2];
	int	i;

	ft_bzero(&flag, sizeof(int) * 2);
	i = (int)ft_strlen(map[*j]) - 2;
	if (map[*j][i] && map[*j][i] != '1')
		return (1);
	while (i > 0 && map[*j][i] && map[*j][i] == '1')
	{
		if (i < (int)ft_strlen(map[*j - 1]))
			if (map[*j - 1][i] && map[*j - 1][i] == '1')
				flag[0] = 1;
		if (i < (int)ft_strlen(map[*j + 1]))
			if (map[*j + 1][i] && map[*j + 1][i] == '1')
				flag[1] = 1;
		i--;
	}
	if (flag[0] == 0 || flag[1] == 0)
		return (1);
	return (0);
}

int	check_elements0b(char **map_temp, t_program *prog, char **data, int *elem)
{
	init(data, map_temp, prog);
	free_2d_array(data);
	data = NULL;
	close(elem[6]);
	free (elem);
	elem = NULL;
	return (0);
}
