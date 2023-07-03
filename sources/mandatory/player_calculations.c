/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_calculations.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkintana <gkintana@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 22:47:50 by gkintana          #+#    #+#             */
/*   Updated: 2022/08/10 20:42:06 by gkintana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>

double	calculate_position_and_vector(t_program *prog, int formula)
{
	double	result;

	result = 0;
	if (formula == 1)
		result = prog->info.pos_x + prog->info.vec_x * prog->info.move_speed;
	else if (formula == 2)
		result = prog->info.pos_y + prog->info.vec_y * prog->info.move_speed;
	else if (formula == 3)
		result = prog->info.pos_x - prog->info.vec_x * prog->info.move_speed;
	else if (formula == 4)
		result = prog->info.pos_y - prog->info.vec_y * prog->info.move_speed;
	return (result);
}

double	calculate_position_and_plane(t_program *prog, int formula)
{
	double	result;

	result = 0;
	if (formula == 1)
		result = prog->info.pos_x - prog->info.plane_x * prog->info.move_speed;
	else if (formula == 2)
		result = prog->info.pos_y - prog->info.plane_y * prog->info.move_speed;
	else if (formula == 3)
		result = prog->info.pos_x + prog->info.plane_x * prog->info.move_speed;
	else if (formula == 4)
		result = prog->info.pos_y + prog->info.plane_y * prog->info.move_speed;
	return (result);
}

double	calculate_rotation(t_program *prog, int formula, double i[])
{
	double	j[2];

	ft_bzero(&j, 2 * sizeof(double));
	j[0] = i[0];
	if (i[3])
		j[0] *= -1;
	if (formula == 1)
		j[1] = i[1] * cos(j[0]) - prog->info.vec_y * sin(j[0]);
	else if (formula == 2)
		j[1] = i[1] * sin(j[0]) + prog->info.vec_y * cos(j[0]);
	else if (formula == 3)
		j[1] = i[2] * cos(j[0]) - prog->info.plane_y * sin(j[0]);
	else if (formula == 4)
		j[1] = i[2] * sin(j[0]) + prog->info.plane_y * cos(j[0]);
	return (j[1]);
}

/*
** i[0] = stores the value of the player's rotate speed
** i[1] = stores a copy of the player's vector x value before updating
** i[2] = stores a copy of the player's plane x value before updating
** i[3] = boolean which indicates if rotation speed is negative
*/
void	horizontal_perspective(t_program *prog, int rotate_left)
{
	double	i[4];

	ft_bzero(&i, 4 * sizeof(double));
	i[0] = prog->info.rotate_speed;
	if (rotate_left == TRUE)
	{
		i[3] = 1;
		i[1] = prog->info.vec_x;
		prog->info.vec_x = calculate_rotation(prog, 1, i);
		prog->info.vec_y = calculate_rotation(prog, 2, i);
		i[2] = prog->info.plane_x;
		prog->info.plane_x = calculate_rotation(prog, 3, i);
		prog->info.plane_y = calculate_rotation(prog, 4, i);
	}
	else
	{
		i[3] = 0;
		i[1] = prog->info.vec_x;
		prog->info.vec_x = calculate_rotation(prog, 1, i);
		prog->info.vec_y = calculate_rotation(prog, 2, i);
		i[2] = prog->info.plane_x;
		prog->info.plane_x = calculate_rotation(prog, 3, i);
		prog->info.plane_y = calculate_rotation(prog, 4, i);
	}
}
