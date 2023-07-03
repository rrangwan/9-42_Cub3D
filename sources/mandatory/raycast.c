/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkintana <gkintana@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/10 14:55:41 by gkintana          #+#    #+#             */
/*   Updated: 2022/08/10 20:43:16 by gkintana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>

void	initialize_t_calculations(t_program *prog, t_calculations *calc, int i)
{
	calc->camera = 2 * i / (double)prog->mlx.win_width - 1;
	calc->ray_vec_x = prog->info.vec_x + prog->info.plane_x * calc->camera;
	calc->ray_vec_y = prog->info.vec_y + prog->info.plane_y * calc->camera;
	calc->delta_x = fabs(1 / calc->ray_vec_x);
	calc->delta_y = fabs(1 / calc->ray_vec_y);
	calc->map_x = (int)prog->info.pos_x;
	calc->map_y = (int)prog->info.pos_y;
}

void	check_vectors(t_program *prog, t_calculations *calc)
{
	if (calc->ray_vec_x < 0)
	{
		calc->offset_x = -1;
		calc->side_dist_x = (prog->info.pos_x - calc->map_x) * calc->delta_x;
	}
	else
	{
		calc->offset_x = 1;
		calc->side_dist_x = (calc->map_x + 1.0 - prog->info.pos_x)
			* calc->delta_x;
	}
	if (calc->ray_vec_y < 0)
	{
		calc->offset_y = -1;
		calc->side_dist_y = (prog->info.pos_y - calc->map_y) * calc->delta_y;
	}
	else
	{
		calc->offset_y = 1;
		calc->side_dist_y = (calc->map_y + 1.0 - prog->info.pos_y)
			* calc->delta_y;
	}
}

void	perform_dda_and_calculate_dist(t_program *prog, t_calculations *calc)
{
	while (TRUE)
	{
		if (calc->side_dist_x < calc->side_dist_y)
		{
			calc->side_dist_x += calc->delta_x;
			calc->map_x += calc->offset_x;
			calc->side = 0;
		}
		else
		{
			calc->side_dist_y += calc->delta_y;
			calc->map_y += calc->offset_y;
			calc->side = 1;
		}
		if (prog->mlx.map[calc->map_y][calc->map_x] == '1')
			break ;
	}
	if (!calc->side)
		calc->perp_dist = calc->side_dist_x - calc->delta_x;
	else
		calc->perp_dist = calc->side_dist_y - calc->delta_y;
}

void	calculate_line(t_program *prog, t_calculations *calc, t_raycast *ray)
{
	ray->line_height = (int)(prog->mlx.win_height / calc->perp_dist);
	ray->start = -ray->line_height / 2 + prog->mlx.win_height / 2;
	if (ray->start < 0)
		ray->start = 0;
	ray->end = ray->line_height / 2 + prog->mlx.win_height / 2;
	if (ray->end >= prog->mlx.win_height)
		ray->end = prog->mlx.win_height - 1;
}

int	raycast_loop(t_program *prog)
{
	t_calculations	calc;
	t_raycast		ray;
	int				i[2];

	ft_bzero(&calc, sizeof(t_calculations));
	ft_bzero(&ray, sizeof(t_raycast));
	ft_bzero(&i, 2 * sizeof(int));
	i[0] = -1;
	while (++i[0] < prog->mlx.win_width)
	{
		initialize_t_calculations(prog, &calc, i[0]);
		check_vectors(prog, &calc);
		perform_dda_and_calculate_dist(prog, &calc);
		calculate_line(prog, &calc, &ray);
		calculate_texture(prog, &calc, &ray);
		save_texture(prog, &calc, &ray, i);
	}
	draw_walls(prog, ray.buffer);
	mlx_put_image_to_window(prog->mlx.ptr, prog->mlx.window,
		prog->mlx.img[0].ptr, 0, 0);
	return (0);
}
