/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkintana <gkintana@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/09 02:00:52 by rrangwan          #+#    #+#             */
/*   Updated: 2022/08/03 13:12:22 by gkintana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D_bonus.h>

char	*init_path(char *str, int *i)
{
	char	*ret;
	int		j;
	int		len;

	j = *i;
	while (!ft_isspace(str[j]))
		j++;
	len = j - *i;
	j = 0;
	ret = (char *)malloc(sizeof(char) * (len + 1));
	if (!ret)
		return (NULL);
	while (!ft_isspace(str[*i]))
	{
		ret[j] = str[*i];
		j++;
		*i += 1;
	}
	ret[j] = '\0';
	return (ret);
}

void	init_mlx(t_program *prog)
{
	prog->mlx.ptr = mlx_init();
	prog->mlx.win_width = WIN_WIDTH;
	prog->mlx.win_height = WIN_HEIGHT;
	prog->mlx.window = mlx_new_window(prog->mlx.ptr, prog->mlx.win_width, \
	prog->mlx.win_height, "cub3D");
}

void	init_images(t_program *prog)
{
	prog->mlx.img[0].ptr = mlx_new_image(prog->mlx.ptr, prog->mlx.win_width, \
	prog->mlx.win_height);
	prog->mlx.img[0].addr = mlx_get_data_addr(prog->mlx.img[0].ptr, \
	&prog->mlx.img[0].bpp, &prog->mlx.img[0].len, &prog->mlx.img[0].endian);
	prog->mlx.img[1].ptr = mlx_xpm_file_to_image(prog->mlx.ptr, \
	prog->tex.north, &prog->tex.width, &prog->tex.height);
	prog->mlx.img[1].pixel = (int *)mlx_get_data_addr(prog->mlx.img[1].ptr, \
	&prog->mlx.img[1].bpp, &prog->mlx.img[1].len, &prog->mlx.img[1].endian);
	prog->mlx.img[2].ptr = mlx_xpm_file_to_image(prog->mlx.ptr, \
	prog->tex.south, &prog->tex.width, &prog->tex.height);
	prog->mlx.img[2].pixel = (int *)mlx_get_data_addr(prog->mlx.img[2].ptr, \
	&prog->mlx.img[2].bpp, &prog->mlx.img[2].len, &prog->mlx.img[2].endian);
	prog->mlx.img[3].ptr = mlx_xpm_file_to_image(prog->mlx.ptr, prog->tex.east, \
	&prog->tex.width, &prog->tex.height);
	prog->mlx.img[3].pixel = (int *)mlx_get_data_addr(prog->mlx.img[3].ptr, \
	&prog->mlx.img[3].bpp, &prog->mlx.img[3].len, &prog->mlx.img[2].endian);
	prog->mlx.img[4].ptr = mlx_xpm_file_to_image(prog->mlx.ptr, prog->tex.west, \
	&prog->tex.width, &prog->tex.height);
	prog->mlx.img[4].pixel = (int *)mlx_get_data_addr(prog->mlx.img[4].ptr, \
	&prog->mlx.img[4].bpp, &prog->mlx.img[4].len, &prog->mlx.img[4].endian);
}

void	init_player(t_program *prog)
{
	set_player_position(prog);
	set_player_orientation(prog);
	prog->info.move_speed = INITIAL_MOVE_SPEED;
	prog->info.rotate_speed = INITIAL_ROTATE_SPEED;
	prog->info.rotate_backup = prog->info.rotate_speed;
	prog->map.scale = 50;
	prog->map.offset_x = 15;
	prog->map.offset_y = 15;
}
