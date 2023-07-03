/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_representation.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkintana <gkintana@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/06 13:39:37 by gkintana          #+#    #+#             */
/*   Updated: 2022/08/06 13:40:12 by gkintana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D_bonus.h>

/*
** draws a simple line which assists the player in visualizing which direction
** they're currently facing
**
** i[0] = offset from player cube's center
** i[1] = calculations for the x-coordinate of a point representing the player's
**        perspective at i[0]'s distance
** i[2] = calculations for the y-coordinate of a point representing the player's
**        perspective at i[0]'s distance
*/
static void	draw_player_perspective(t_program *prog)
{
	int	i[3];

	ft_bzero(&i, sizeof(int) * 3);
	i[0] = 5;
	while (++i[0] < 15)
	{
		i[1] = prog->info.vec_x * i[0] + prog->mlx.win_width / prog->map.scale
			* 7 + prog->map.offset_x + 0.5;
		i[2] = prog->info.vec_y * i[0] + prog->mlx.win_height / prog->map.scale
			* 7 + prog->map.offset_y / 2 + 1;
		put_pixel_at_addr(&prog->mlx.img[0], i[1], i[2], 0xFFFF00);
	}
}

/*
** provides an estimate of the player's location based on the current block
** they're standing on
**
** i[0] = player cube size
** i[1] = player's y-axis
** i[2] = player's x-axis
** i[3] = player's current x-coordinate after scaling
** i[4] = player's current y-coordinate after scaling
*/
void	draw_player(t_program *prog)
{
	int	i[5];

	i[0] = 6;
	i[1] = -1;
	while (++i[1] < i[0])
	{
		i[2] = -1;
		i[3] = 0;
		i[4] = 0;
		while (++i[2] < i[0])
		{
			i[3] = i[2] + prog->mlx.win_width / prog->map.scale
				* 7 + prog->mlx.win_width / prog->map.scale / 2 - (i[0] / 2);
			i[4] = i[1] + prog->mlx.win_height / prog->map.scale
				* 7 + prog->mlx.win_height / prog->map.scale / 2 - (i[0] / 2);
			put_pixel_at_addr(&prog->mlx.img[0], i[3], i[4], 0xFF0000);
		}
	}
	draw_player_perspective(prog);
}
