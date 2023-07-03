/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_textures.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkintana <gkintana@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/29 13:03:29 by gkintana          #+#    #+#             */
/*   Updated: 2022/08/01 18:01:18 by gkintana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>

void	calculate_texture(t_program *prog, t_calculations *calc, t_raycast *ray)
{
	if (!calc->side)
		ray->wall = prog->info.pos_y + calc->perp_dist * calc->ray_vec_y;
	else
		ray->wall = prog->info.pos_x + calc->perp_dist * calc->ray_vec_x;
	ray->wall -= floor(ray->wall);
	ray->texture_x = (int)(ray->wall * (double)prog->tex.width);
	if (!calc->side && calc->ray_vec_x > 0)
		ray->texture_x = prog->tex.width - ray->texture_x - 1;
	else if (calc->side && calc->ray_vec_y < 0)
		ray->texture_x = prog->tex.width - ray->texture_x - 1;
	ray->step = 1.0 * prog->tex.height / ray->line_height;
	ray->texture_pos = (ray->start - prog->mlx.win_height / 2
			+ ray->line_height / 2) * ray->step;
}

static void	determine_texture(t_program *prog, t_calculations *calc,
		t_raycast *ray, int coordinate)
{
	if (calc->side && calc->offset_y < 0)
		ray->color = prog->mlx.img[1].pixel[coordinate];
	else if (calc->side && calc->ray_vec_y > 0)
		ray->color = prog->mlx.img[2].pixel[coordinate];
	else if (!calc->side && calc->ray_vec_x > 0)
		ray->color = prog->mlx.img[3].pixel[coordinate];
	else if (!calc->side && calc->ray_vec_x < 0)
		ray->color = prog->mlx.img[4].pixel[coordinate];
}

void	save_texture(t_program *prog, t_calculations *calc,
		t_raycast *ray, int i[])
{
	int	coordinate;

	coordinate = 0;
	i[1] = ray->start;
	while (i[1] < ray->end)
	{
		ray->texture_y = (int)ray->texture_pos & (prog->tex.height - 1);
		ray->texture_pos += ray->step;
		coordinate = prog->tex.height * ray->texture_y + ray->texture_x;
		determine_texture(prog, calc, ray, coordinate);
		if (!ray->color)
			ray->buffer[i[1]][i[0]] = 1;
		else
			ray->buffer[i[1]][i[0]] = ray->color;
		i[1]++;
	}
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

	i[0] = -1;
	while (++i[0] < prog->mlx.win_height)
	{
		i[1] = -1;
		while (++i[1] < prog->mlx.win_width)
		{
			if (!buffer[i[0]][i[1]] && i[0] <= prog->mlx.win_height / 2)
				put_pixel_at_addr(&prog->mlx.img[0], i[1], i[0],
					prog->tex.rgb.ceiling);
			else if (!buffer[i[0]][i[1]] && i[0] > prog->mlx.win_height / 2)
				put_pixel_at_addr(&prog->mlx.img[0], i[1], i[0],
					prog->tex.rgb.floor);
			else
				put_pixel_at_addr(&prog->mlx.img[0], i[1], i[0],
					buffer[i[0]][i[1]]);
		}
	}
}
