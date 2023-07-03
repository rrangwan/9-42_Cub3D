/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkintana <gkintana@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/07 14:03:49 by gkintana          #+#    #+#             */
/*   Updated: 2022/08/08 11:56:52 by gkintana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D_bonus.h>

/*
** counts then returns the total number of elements in prog->mlx.map
*/
int	get_map_height(t_program *prog)
{
	int	height;

	height = 0;
	while (prog->mlx.map[height])
		height++;
	return (height);
}

/*
** returns an index number which specifies the location of the first wall
** character in a given string
*/
int	find_wall_start(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
		if (str[i] == '1')
			return (i);
	return (0);
}

/*
** checks if the values being used when accessing prog->mlx.map are within the
** limits of the allocation
**
** When checking prog->mlx.map[], we have to ensure that the value of the
** variable is greater than or equal to zero, and less than the map's total
** height. When checking prog->mlx.map[][], we test if the value of the
** variable is greater than or equal to zero, and less than the current map
** line's length
*/
int	is_valid_coordinate(t_program *prog, int j[])
{
	if (j[0] >= 0 && j[0] < get_map_height(prog)
		&& j[1] >= 0 && j[1] < (int)ft_strlen(prog->mlx.map[j[0]]))
		return (1);
	return (0);
}
