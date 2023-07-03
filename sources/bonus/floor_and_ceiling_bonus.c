/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   floor_and_ceiling_bonus.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkintana <gkintana@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/30 12:50:21 by gkintana          #+#    #+#             */
/*   Updated: 2022/08/10 20:30:17 by gkintana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D_bonus.h>

/*
** combines the individual rgb components by computing for their hexadecimal
** values and returns the decimal representation that particular combination
**
** formula was based on the calculations provided at this website
** https://www.rapidtables.com/convert/number/hex-to-decimal.html
*/
static int	convert_hex_to_int(t_rgb *rgb, int is_floor)
{
	if (is_floor == TRUE)
		return ((int)(((rgb->floor_r / 16) * pow(16, 5))
			+ ((rgb->floor_r % 16) * pow(16, 4))
			+ ((rgb->floor_g / 16) * pow(16, 3))
			+ ((rgb->floor_g % 16) * pow(16, 2))
			+ ((rgb->floor_b / 16) * pow(16, 1))
			+ ((rgb->floor_b % 16) * pow(16, 0))));
	else
		return ((int)(((rgb->ceiling_r / 16) * pow(16, 5))
			+ ((rgb->ceiling_r % 16) * pow(16, 4))
			+ ((rgb->ceiling_g / 16) * pow(16, 3))
			+ ((rgb->ceiling_g % 16) * pow(16, 2))
			+ ((rgb->ceiling_b / 16) * pow(16, 1))
			+ ((rgb->ceiling_b % 16) * pow(16, 0))));
}

/*
** sets the respective rgb value to the t_rgb struct for later use in the
** get_floor_and_ceiling_rgb & print_rgb_info functions
*/
static void	save_rgb_components(t_rgb *rgb, char **rgb_array[])
{
	rgb->floor_r = ft_atoi(rgb_array[0][0]);
	rgb->floor_g = ft_atoi(rgb_array[0][1]);
	rgb->floor_b = ft_atoi(rgb_array[0][2]);
	rgb->ceiling_r = ft_atoi(rgb_array[1][0]);
	rgb->ceiling_g = ft_atoi(rgb_array[1][1]);
	rgb->ceiling_b = ft_atoi(rgb_array[1][2]);
}

/*
** prints the rgb hex and int values of the floor and ceiling colors.
** Will be mainly used for double checking & evaluations
*/
void	print_rgb_info(t_rgb *rgb)
{
	printf("Floor RGB (Hex Value) = %c%c%c%c%c%c\n",
		HEX_SYSTEM[rgb->floor_r / 16], HEX_SYSTEM[rgb->floor_r % 16],
		HEX_SYSTEM[rgb->floor_g / 16], HEX_SYSTEM[rgb->floor_g % 16],
		HEX_SYSTEM[rgb->floor_b / 16], HEX_SYSTEM[rgb->floor_b % 16]);
	printf("Floor RGB (Int Value) = %d\n", rgb->floor);
	printf("Ceiling RGB (Hex Value) = %c%c%c%c%c%c\n",
		HEX_SYSTEM[rgb->ceiling_r / 16], HEX_SYSTEM[rgb->ceiling_r % 16],
		HEX_SYSTEM[rgb->ceiling_g / 16], HEX_SYSTEM[rgb->ceiling_g % 16],
		HEX_SYSTEM[rgb->ceiling_b / 16], HEX_SYSTEM[rgb->ceiling_b % 16]);
	printf("Ceiling RGB (Int Value) = %d\n", rgb->ceiling);
}

// https://www.developintelligence.com/blog/2017/02/rgb-to-hex-understanding
// -the-major-web-color-codes/
/*
** saves the rgb information from prog->tex.floor & prog->tex.ceiling to the
** t_rgb struct and computes for the hexadecimal representation of each
** individual rgb component. Afterwards, it takes the sum of all components
** then saves it to prog->tex.rgb.floor & prog->tex.rgb.ceiling
**
** rgb_array[0] = 2d array containing the rgb values of the floor's color
** rgb_array[0][0] = Floor R
** rgb_array[0][1] = Floor G
** rgb_array[0][2] = Floor B
** rgb_array[1] = 2d array containing the rgb values of the ceiling's color
** rgb_array[1][0] = Ceiling R
** rgb_array[1][1] = Ceiling G
** rgb_array[1][2] = Ceiling B
*/
void	get_floor_and_ceiling_rgb(t_program *prog)
{
	char	**rgb_array[2];

	rgb_array[0] = ft_split(prog->tex.floor, ',');
	rgb_array[1] = ft_split(prog->tex.ceiling, ',');
	save_rgb_components(&prog->tex.rgb, rgb_array);
	prog->tex.rgb.floor = convert_hex_to_int(&prog->tex.rgb, TRUE);
	prog->tex.rgb.ceiling = convert_hex_to_int(&prog->tex.rgb, FALSE);
	free_2d_array(rgb_array[0]);
	free_2d_array(rgb_array[1]);
}
