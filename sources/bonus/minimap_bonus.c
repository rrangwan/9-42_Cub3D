/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkintana <gkintana@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/05 14:58:32 by gkintana          #+#    #+#             */
/*   Updated: 2022/08/10 20:32:58 by gkintana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D_bonus.h>

/*
** draws a large black box on the screen which will serve as the background of
** our minimap
**
** i[0] = index for minimap background's y-axis
** i[1] = index for minimap background's x-axis
*/
static void	draw_map_box(t_program *prog)
{
	int	i[2];

	ft_bzero(&i, sizeof(int) * 2);
	i[0] = prog->mlx.win_height / prog->map.scale - 2;
	while (++i[0] < prog->mlx.win_height / prog->map.scale * 14)
	{
		i[1] = prog->mlx.win_width / prog->map.scale - 2;
		while (++i[1] < prog->mlx.win_width / prog->map.scale * 14)
			put_pixel_at_addr(&prog->mlx.img[0], i[1], i[0], 0x000000);
	}
}

/*
** draws a block of a specific color to our prog->mlx.img[0] based on the
** coordinates set at the x and y parameters
**
** i[0] = pixel position with respect to the block's y-axis
** i[1] = pixel position with respect to the block's x-axis
** i[2] = pixel position + x-offset
** i[3] = pixel position + y-offset
*/
static void	draw_block(t_program *prog, int x, int y, int color)
{
	int	i[4];

	i[0] = -1;
	while (++i[0] < prog->mlx.win_height / prog->map.scale - 1)
	{
		i[1] = -1;
		while (++i[1] < prog->mlx.win_width / prog->map.scale - 1)
		{
			i[2] = i[1] + prog->mlx.win_width / prog->map.scale + x;
			i[3] = i[0] + prog->mlx.win_height / prog->map.scale + y;
			put_pixel_at_addr(&prog->mlx.img[0], i[2], i[3], color);
		}
	}
}

/*
** checks if the block at a certain distance from the player's x and y position
** should be rendered to the minimap
**
** j[0] = stores the result of player's y-position + current y-block
** j[1] = stores the result of player's x-position + current x-block
*/
static int	check_map_coordinates(t_program *prog, int i[], int is_wall,
			int is_space)
{
	int	j[2];

	j[0] = (int)prog->info.pos_y + i[0];
	j[1] = (int)prog->info.pos_x + i[2];
	if (is_wall == TRUE)
	{
		if (is_valid_coordinate(prog, j) && prog->mlx.map[j[0]][j[1]] == '1')
			return (1);
	}
	else if (is_space == TRUE)
	{
		if (is_valid_coordinate(prog, j) && prog->mlx.map[j[0]][j[1]] == ' '
			&& j[1] < find_wall_start(prog->mlx.map[j[0]]))
			return (1);
		else if (is_valid_coordinate(prog, j)
			&& prog->mlx.map[j[0]][j[1]] == ' ' && !space_is_inside(prog, j))
			return (1);
	}
	else if (is_valid_coordinate(prog, j)
		&& ft_strchr(" 0NSEW", prog->mlx.map[j[0]][j[1]]))
		return (1);
	return (0);
}

/*
** draws the minimap to the top left corner of our prog->mlx.img[0]
**
** i[0] = current y-block
** i[1] = offset value that will be multiplied to block height
** i[2] = current x-block
** i[3] = offset value that will be multiplied to block width
** i[4] = result of i[3] * block width
** i[5] = result of i[1] * block height
*/
void	draw_map(t_program *prog)
{
	int	i[6];

	draw_map_box(prog);
	ft_bzero(&i, sizeof(int) * 6);
	i[0] = -7;
	i[1] = 0;
	while (++i[0] < 7)
	{
		i[2] = -7;
		i[3] = 0;
		while (++i[2] < 7)
		{
			i[4] = i[3] * prog->mlx.win_width / prog->map.scale;
			i[5] = i[1] * prog->mlx.win_height / prog->map.scale;
			if (check_map_coordinates(prog, i, TRUE, FALSE))
				draw_block(prog, i[4], i[5], 0x3313294B);
			else if (check_map_coordinates(prog, i, FALSE, TRUE))
				draw_block(prog, i[4], i[5], 0x000000);
			else if (check_map_coordinates(prog, i, FALSE, FALSE))
				draw_block(prog, i[4], i[5], 0x33777777);
			i[3]++;
		}
		i[1]++;
	}
}
