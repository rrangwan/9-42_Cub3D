/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkintana <gkintana@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/02 01:01:52 by gkintana          #+#    #+#             */
/*   Updated: 2022/08/01 17:11:07 by gkintana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D_bonus.h>

int	main(int argc, char **argv)
{
	t_program	prog;

	if (argc == 2)
	{
		ft_bzero(&prog, sizeof(t_program));
		check_map_validity(argv[1]);
		check_map_extension(argv[1]);
		if (!check_elements(argv[1], &prog))
		{
			get_floor_and_ceiling_rgb(&prog);
			raycast_loop(&prog);
			mlx_mouse_hide(prog.mlx.ptr, prog.mlx.window);
			mlx_hook(prog.mlx.window, 6, 1L << 6, mouse_events, &prog);
			mlx_hook(prog.mlx.window, 2, 1L << 0, key_events, &prog);
			mlx_hook(prog.mlx.window, 17, 1L << 17, close_window, &prog);
			mlx_loop(prog.mlx.ptr);
			return (0);
		}
	}
	ft_putstr_fd("Error\nInvalid Arguments\n", 2);
	return (1);
}
