/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_check.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkintana <gkintana@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/07 14:03:51 by gkintana          #+#    #+#             */
/*   Updated: 2022/08/08 11:56:38 by gkintana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D_bonus.h>

static int	find_north_wall(t_program *prog, int j[])
{
	int	x;
	int	y;

	x = j[1];
	y = j[0];
	while (--y > -1)
		if (prog->mlx.map[y][x] == '1')
			return (1);
	return (0);
}

static int	find_south_wall(t_program *prog, int j[])
{
	int	x;
	int	y;

	x = j[1];
	y = j[0];
	while (prog->mlx.map[++y] && y < get_map_height(prog) - 1)
		if (prog->mlx.map[y][x] && prog->mlx.map[y][x] == '1')
			return (1);
	return (0);
}

static int	find_east_wall(char *str, int j)
{
	while (str[++j])
		if (str[j] == '1')
			return (1);
	return (0);
}

static int	find_west_wall(char *str, int j)
{
	while (--j > -1)
		if (str[j] == '1')
			return (1);
	return (0);
}

int	space_is_inside(t_program *prog, int j[])
{
	if (j[1] > find_wall_start(prog->mlx.map[j[0]])
		&& find_north_wall(prog, j)
		&& find_south_wall(prog, j)
		&& find_east_wall(prog->mlx.map[j[0]], j[1])
		&& find_west_wall(prog->mlx.map[j[0]], j[1]))
		return (1);
	return (0);
}
