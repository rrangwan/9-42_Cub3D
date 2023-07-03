/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkintana <gkintana@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/10 14:56:22 by gkintana          #+#    #+#             */
/*   Updated: 2022/08/08 11:56:17 by gkintana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D_bonus.h>

static int	convert_hex_to_int(int r, int g, int b)
{
	return ((int)(((r / 16) * pow(16, 5))
		+ ((r % 16) * pow(16, 4))
		+ ((g / 16) * pow(16, 3))
		+ ((g % 16) * pow(16, 2))
		+ ((b / 16) * pow(16, 1))
		+ ((b % 16) * pow(16, 0))));
}

/*
** stores a copy of each individual floor and ceiling rgb component to the j[8]
** array, which will be used for floor & ceiling distance shading
**
** j[0] = floor r
** j[1] = floor g
** j[2] = floor b
** j[3] = ceiling r
** j[4] = ceiling g
** j[5] = ceiling b
** j[6] = shaded floor color
** j[7] = shaded ceiling color
*/
static void	copy_and_adjust_rgb(t_program *prog, int j[])
{
	j[0] = prog->tex.rgb.floor_r;
	while (j[0] % 5 != 0 && j[0] > 0)
		j[0]--;
	j[1] = prog->tex.rgb.floor_g;
	while (j[1] % 5 != 0 && j[1] > 0)
		j[1]--;
	j[2] = prog->tex.rgb.floor_b;
	while (j[2] % 5 != 0 && j[2] > 0)
		j[2]--;
	j[3] = prog->tex.rgb.ceiling_r;
	while (j[3] % 5 != 0 && j[3] > 0)
		j[3]--;
	j[4] = prog->tex.rgb.ceiling_g;
	while (j[4] % 5 != 0 && j[4] > 0)
		j[4]--;
	j[5] = prog->tex.rgb.ceiling_b;
	while (j[5] % 5 != 0 && j[5] > 0)
		j[5]--;
	j[6] = convert_hex_to_int(j[0], j[1], j[2]);
	j[7] = convert_hex_to_int(j[3], j[4], j[5]);
}

/*
** k[0] = window height / 2
** k[1] = player's vertical perspective factor
** l[0] = ceiling height factor
** l[1] = ceiling distance shading factor
*/
static int	draw_ceiling(t_program *prog, int (*buffer)[prog->mlx.win_width],
	int i[], int j[])
{
	int		k[2];
	double	l[2];

	k[0] = prog->mlx.win_height / 2;
	k[1] = prog->info.pitch;
	l[0] = 0.850;
	l[1] = 1;
	while (l[0] < 1 && l[1] > 0)
	{
		if (!buffer[i[0]][i[1]] && i[0] < k[0] * l[0] + k[1])
		{
			if (l[0] == 0.850)
				put_pixel_at_addr(&prog->mlx.img[0], i[1], i[0],
					prog->tex.rgb.ceiling);
			else
				put_pixel_at_addr(&prog->mlx.img[0], i[1], i[0], j[7] * l[1]);
			return (1);
		}
		else
		{
			l[0] += 0.025;
			l[1] -= 0.2;
		}
	}
	return (0);
}

/*
** k[0] = window height / 2
** k[1] = player's vertical perspective factor
** l[0] = floor height factor
** l[1] = floor distance shading factor
*/
static int	draw_floor(t_program *prog, int (*buffer)[prog->mlx.win_width],
		int i[], int j[])
{
	int		k[2];
	double	l[2];

	k[0] = prog->mlx.win_height / 2;
	k[1] = prog->info.pitch;
	l[0] = 1.150;
	l[1] = 1;
	while (l[0] > 1 && l[1] > 0)
	{
		if (!buffer[i[0]][i[1]] && i[0] > k[0] * l[0] + k[1])
		{
			if (l[0] == 1.150)
				put_pixel_at_addr(&prog->mlx.img[0], i[1], i[0],
					prog->tex.rgb.floor);
			else
				put_pixel_at_addr(&prog->mlx.img[0], i[1], i[0], j[6] * l[1]);
			return (1);
		}
		else
		{
			l[0] -= 0.025;
			l[1] -= 0.2;
		}
	}
	return (0);
}

// https://stackoverflow.com/questions/20297594/warning-expected-int-but-argume
// nt-is-of-type-int-sizetypen
/*
** transfers each individual pixel from the pre-rendered texture buffer to the
** output image's address
**
** i[0] = index for y-axis
** i[1] = index for x-axis
*/
void	draw_walls(t_program *prog, int (*buffer)[prog->mlx.win_width])
{
	int	i[2];
	int	j[8];

	ft_bzero(&j, sizeof(int) * 8);
	copy_and_adjust_rgb(prog, j);
	i[0] = -1;
	while (++i[0] < prog->mlx.win_height)
	{
		i[1] = -1;
		while (++i[1] < prog->mlx.win_width)
		{
			if (!draw_ceiling(prog, buffer, i, j))
				if (!draw_floor(prog, buffer, i, j))
					put_pixel_at_addr(&prog->mlx.img[0], i[1], i[0],
						buffer[i[0]][i[1]]);
		}
	}
}
