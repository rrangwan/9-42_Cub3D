/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkintana <gkintana@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/09 02:02:04 by gkintana          #+#    #+#             */
/*   Updated: 2022/07/29 19:10:38 by gkintana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D_bonus.h>

/*
** this is the my_mlx_pixel_put function from the minilibx documentation
*/
void	put_pixel_at_addr(t_image *img, int x, int y, int color)
{
	char			*pixel;
	unsigned int	pixel_position;

	pixel_position = (y * img->len) + (x * (img->bpp >> 3));
	pixel = img->addr + pixel_position;
	*(unsigned int *)pixel = color;
}

void	free_2d_array(char **array)
{
	size_t	i;

	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
	array = NULL;
}

/*
** used to renew the image according to the changes made from either pressing
** some specific keys on the keyboard or based from the movement of the mouse
**
** this function destroys the current image and creates a new one instead of
** reassigning new pixels over the old image. Observed that it reduced cpu
** load by about 2-3%, however it does affect the memory wherein it always
** fluctuates between 0.2 and 0.4 which could be misinterpreted by our
** evaluators as mishandling of memory usage
*/
void	update_frame(t_program *prog)
{
	int		i[2];
	int		*j[3];
	char	*temp;

	i[0] = prog->mlx.win_width;
	i[1] = prog->mlx.win_height;
	j[0] = &prog->mlx.img[0].bpp;
	j[1] = &prog->mlx.img[0].len;
	j[2] = &prog->mlx.img[0].endian;
	temp = mlx_get_data_addr(prog->mlx.img[0].ptr, j[0], j[1], j[2]);
	mlx_destroy_image(prog->mlx.ptr, prog->mlx.img[0].ptr);
	prog->mlx.img[0].ptr = mlx_new_image(prog->mlx.ptr, i[0], i[1]);
	prog->mlx.img[0].addr = temp;
	mlx_clear_window(prog->mlx.ptr, prog->mlx.window);
	raycast_loop(prog);
}

int	close_window(t_program *prog)
{
	free(prog->tex.north);
	free(prog->tex.south);
	free(prog->tex.east);
	free(prog->tex.west);
	free(prog->tex.floor);
	free(prog->tex.ceiling);
	free_2d_array(prog->mlx.map);
	mlx_destroy_image(prog->mlx.ptr, prog->mlx.img[0].ptr);
	mlx_destroy_image(prog->mlx.ptr, prog->mlx.img[1].ptr);
	mlx_destroy_image(prog->mlx.ptr, prog->mlx.img[2].ptr);
	mlx_destroy_image(prog->mlx.ptr, prog->mlx.img[3].ptr);
	mlx_destroy_image(prog->mlx.ptr, prog->mlx.img[4].ptr);
	mlx_clear_window(prog->mlx.ptr, prog->mlx.window);
	mlx_destroy_window(prog->mlx.ptr, prog->mlx.window);
	exit(0);
}
