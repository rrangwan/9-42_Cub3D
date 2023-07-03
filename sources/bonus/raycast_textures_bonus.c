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

#include <cub3D_bonus.h>

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
	ray->texture_pos = (ray->start - prog->info.pitch
			- prog->mlx.win_height / 2 + ray->line_height / 2) * ray->step;
}

// https://permadi.com/1996/05/ray-casting-tutorial-19/#SHADING
// https://stackoverflow.com/questions/4801366/convert-rgb-values-to-integer#
// :~:text=To%20set%20the%20values%20from,(x%2C%20y%2C%20rgb)%3B
static void	apply_shade(t_calculations *calc, t_raycast *ray)
{
	double	color_intensity;
	int		i[6];

	color_intensity = 1 / (calc->perp_dist / 3.75);
	i[0] = ((ray->color >> 16) & 255);
	i[1] = (ray->color >> 8) & 255;
	i[2] = ray->color & 255;
	i[3] = color_intensity * i[0];
	i[4] = color_intensity * i[1];
	i[5] = color_intensity * i[2];
	if (i[0] > i[3])
		i[0] = i[3];
	if (i[1] > i[4])
		i[1] = i[4];
	if (i[2] > i[5])
		i[2] = i[5];
	ray->color = pow(16, 4) * i[0] + pow(16, 2) * i[1] + i[2];
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
		apply_shade(calc, ray);
		if (calc->side)
			apply_shade(calc, ray);
		if (!ray->color)
			ray->buffer[i[1]][i[0]] = 1;
		else
			ray->buffer[i[1]][i[0]] = ray->color;
		i[1]++;
	}
}
