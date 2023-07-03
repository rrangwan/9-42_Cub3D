/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyboard_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkintana <gkintana@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/09 01:54:46 by gkintana          #+#    #+#             */
/*   Updated: 2022/08/10 20:29:05 by gkintana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D_bonus.h>

static void	vertical_movement(t_program *prog, int move_forward)
{
	int	i[2];

	ft_bzero(&i, 2 * sizeof(int));
	if (move_forward == TRUE)
	{
		i[0] = (int)(calculate_position_and_vector(prog, 1));
		i[1] = (int)(calculate_position_and_vector(prog, 2));
		if (prog->mlx.map[(int)prog->info.pos_y][i[0]] != '1')
			prog->info.pos_x += prog->info.vec_x * prog->info.move_speed;
		if (prog->mlx.map[i[1]][(int)prog->info.pos_x] != '1')
			prog->info.pos_y += prog->info.vec_y * prog->info.move_speed;
	}
	else
	{
		i[0] = (int)(calculate_position_and_vector(prog, 3));
		i[1] = (int)(calculate_position_and_vector(prog, 4));
		if (prog->mlx.map[(int)prog->info.pos_y][i[0]] != '1')
			prog->info.pos_x -= prog->info.vec_x * prog->info.move_speed;
		if (prog->mlx.map[i[1]][(int)prog->info.pos_x] != '1')
			prog->info.pos_y -= prog->info.vec_y * prog->info.move_speed;
	}
}

static void	horizontal_movement(t_program *prog, int move_left)
{
	int	i[2];

	ft_bzero(&i, 2 * sizeof(int));
	if (move_left == TRUE)
	{
		i[0] = (int)(calculate_position_and_plane(prog, 1));
		i[1] = (int)(calculate_position_and_plane(prog, 2));
		if (prog->mlx.map[(int)prog->info.pos_y][i[0]] != '1')
			prog->info.pos_x -= prog->info.plane_x * prog->info.move_speed;
		if (prog->mlx.map[i[1]][(int)prog->info.pos_x] != '1')
			prog->info.pos_y -= prog->info.plane_y * prog->info.move_speed;
	}
	else
	{
		i[0] = (int)(calculate_position_and_plane(prog, 3));
		i[1] = (int)(calculate_position_and_plane(prog, 4));
		if (prog->mlx.map[(int)prog->info.pos_y][i[0]] != '1')
			prog->info.pos_x += prog->info.plane_x * prog->info.move_speed;
		if (prog->mlx.map[i[1]][(int)prog->info.pos_x] != '1')
			prog->info.pos_y += prog->info.plane_y * prog->info.move_speed;
	}
}

static void	change_mouse_lock_status(t_program *prog)
{
	if (!prog->mouse.lock)
	{
		prog->mouse.lock = 1;
		mlx_hook(prog->mlx.window, 6, 1L << 6, NULL, NULL);
		mlx_mouse_show(prog->mlx.ptr, prog->mlx.window);
	}
	else
	{
		prog->mouse.lock = 0;
		mlx_hook(prog->mlx.window, 6, 1L << 6, mouse_events, prog);
		mlx_mouse_hide(prog->mlx.ptr, prog->mlx.window);
	}
}

int	key_events(int input, t_program *prog)
{
	if (input == KEYCODE_ESC)
		close_window(prog);
	else if (input == KEYCODE_W)
		vertical_movement(prog, TRUE);
	else if (input == KEYCODE_S)
		vertical_movement(prog, FALSE);
	else if (input == KEYCODE_A)
		horizontal_movement(prog, TRUE);
	else if (input == KEYCODE_D)
		horizontal_movement(prog, FALSE);
	else if (input == KEYCODE_LEFT)
		horizontal_perspective(prog, TRUE);
	else if (input == KEYCODE_RIGHT)
		horizontal_perspective(prog, FALSE);
	else if (input == KEYCODE_UP)
		vertical_perspective(prog, TRUE);
	else if (input == KEYCODE_DOWN)
		vertical_perspective(prog, FALSE);
	else if (input == KEYCODE_L)
		change_mouse_lock_status(prog);
	update_frame(prog);
	return (0);
}
