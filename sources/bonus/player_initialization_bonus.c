/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_initialization.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkintana <gkintana@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/29 12:10:53 by gkintana          #+#    #+#             */
/*   Updated: 2022/07/29 12:11:46 by gkintana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D_bonus.h>

/*
** checks if the current index being accessed in the map is one of the following
** characters "N or S or E or W"
*/
static int	is_valid_start_position(t_program *prog, int i[])
{
	if (prog->mlx.map[i[0]][i[1]] == 'N'
		|| prog->mlx.map[i[0]][i[1]] == 'S'
		|| prog->mlx.map[i[0]][i[1]] == 'E'
		|| prog->mlx.map[i[0]][i[1]] == 'W')
		return (TRUE);
	return (FALSE);
}

/*
** parses the map and sets the player's starting location at the first
** occurrence of the following characters "N or S or E or W".
** furthermore, it also saves the starting orientation to the structure
** which will be used in the set_player_orientation function
**
** i[0] = index for y-axis of map
** i[1] = index for x-axis of map
** i[2] = acts like a boolean to indicate if the player's starting
**        location has been set
*/
void	set_player_position(t_program *prog)
{
	int	i[3];

	ft_bzero(&i, 3 * sizeof(int));
	i[0] = -1;
	while (prog->mlx.map[++i[0]] && !i[2])
	{
		i[1] = -1;
		while (prog->mlx.map[i[0]][++i[1]] && !i[2])
		{
			if (is_valid_start_position(prog, i) == TRUE)
			{
				prog->info.pos_x = i[1] + 0.50;
				prog->info.pos_y = i[0] + 0.50;
				i[2] = 1;
			}
		}
	}
	if (prog->mlx.map[(int)prog->info.pos_y][(int)prog->info.pos_x] == 'N')
		prog->info.orientation = 1;
	else if (prog->mlx.map[(int)prog->info.pos_y][(int)prog->info.pos_x] == 'S')
		prog->info.orientation = 2;
	else if (prog->mlx.map[(int)prog->info.pos_y][(int)prog->info.pos_x] == 'E')
		prog->info.orientation = 3;
	else if (prog->mlx.map[(int)prog->info.pos_y][(int)prog->info.pos_x] == 'W')
		prog->info.orientation = 4;
}

/*
** sets the player's initial facing direction according to the direction
** specified in the map file
*/
void	set_player_orientation(t_program *prog)
{
	if (prog->info.orientation == 1)
	{
		prog->info.vec_y = -1;
		prog->info.plane_x = 0.66;
	}
	else if (prog->info.orientation == 2)
	{
		prog->info.vec_y = 1;
		prog->info.plane_x = -0.66;
	}
	else if (prog->info.orientation == 3)
	{
		prog->info.vec_x = 1;
		prog->info.plane_y = 0.66;
	}
	else if (prog->info.orientation == 4)
	{
		prog->info.vec_x = -1;
		prog->info.plane_y = -0.66;
	}
}
