/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkintana <gkintana@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/29 12:04:39 by gkintana          #+#    #+#             */
/*   Updated: 2022/08/10 20:33:30 by gkintana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D_bonus.h>

#if __APPLE__
/*
** event handler for mouse inputs. Lowers the camera rotation speed before
** calculating and updating the frame for a smoother experience, then sets it
** back to its original value
*/
int	mouse_events(int x, int y, t_program *prog)
{
	(void)y;
	prog->info.rotate_speed = 0.0435;
	if (x < prog->mlx.win_width / 2)
		horizontal_perspective(prog, TRUE);
	else
		horizontal_perspective(prog, FALSE);
	update_frame(prog);
	prog->info.rotate_speed = prog->info.rotate_backup;
	mlx_mouse_move(prog->mlx.window, prog->mlx.win_width / 2,
		prog->mlx.win_height / 2);
	return (0);
}
#endif

#if __linux__
/*
** calls the mlx_mouse_get_pos function to update the t_mouse structure. Had
** to separate it from mouse_events since it never stopped rotating on linux
*/
static void	update_mouse_coordinates(t_program *prog)
{
	mlx_mouse_get_pos(prog->mlx.ptr, prog->mlx.window, &prog->mouse.new_x,
		&prog->mouse.new_y);
}

/*
** event handler for mouse inputs. Lowers the camera rotation speed before
** calculating and updating the frame for a smoother experience, then sets it
** back to its original value
*/
int	mouse_events(int x, int y, t_program *prog)
{
	(void)y;
	update_mouse_coordinates(prog);
	prog->info.rotate_speed = 0.0175;
	if (prog->mouse.new_x < x)
		horizontal_perspective(prog, TRUE);
	else
		horizontal_perspective(prog, FALSE);
	update_frame(prog);
	prog->info.rotate_speed = prog->info.rotate_backup;
	return (0);
}
#endif
